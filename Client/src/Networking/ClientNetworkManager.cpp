////////////////////////////////////////////////////////////////////////////////
// File:        ClientNetworkManager.cpp
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ClientNetworkManager.h"
#include "DependencyInjector.h"

#ifndef SEND_MESSAGE_POOL_SIZE
#define SEND_MESSAGE_POOL_SIZE 200
#endif

namespace Novaland::Networking
{
ClientNetworkManager::ClientNetworkManager() : ANetworkManager()
{
    Dependency::Register<ClientNetworkManager>(this);
    send_queue = new SPSCQueue<SendMessageData>(SEND_MESSAGE_POOL_SIZE);
    is_connected = false;
}

ClientNetworkManager::~ClientNetworkManager()
{
    Dependency::Unregister<ClientNetworkManager>();
    delete send_queue;
}

void ClientNetworkManager::Send(Message *message, SendMode send_mode)
{
    SendMessageData data{};
    data.message = message;
    data.send_mode = send_mode;

    auto result = send_queue->try_push(data);
    if (result == false)
    {
        Logger::Error("Failed to send message to queue.");
    }
}

void ClientNetworkManager::SendMessage(const SendMessageData &send_message_data)
{
    size_t total_size = sizeof(GameTag) + send_message_data.message->length;
    u32 flag =
        send_message_data.send_mode == SendMode::Reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNSEQUENCED;
    ENetPacket *packet = enet_packet_create(send_message_data.message->GetRawData(), total_size, flag);
    enet_peer_send(m_connection->peer, 0, packet);
    ReleaseOutcomingMessage((send_message_data.message));
}

void ClientNetworkManager::SendMessageQueue()
{
    while (!send_queue->empty())
    {
        SendMessageData data = *send_queue->front();
        send_queue->pop();
        SendMessage(data);
    }
}

void ClientNetworkManager::Disconnect()
{
    if (!is_connected)
    {
        return;
    }
    is_connected = false;
    is_running = false;
    io_thread->join();
    enet_peer_disconnect(m_connection->peer, 0);

    uint8_t disconnected = false;
    /* Allow up to 3 seconds for the disconnect to succeed
     * and drop any packets received packets.
     */
    ENetEvent event;
    const u32 timeout = 3000;
    while (!disconnected && enet_host_service(host, &event, timeout) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            disconnected = true;
            break;
        default:
            break;
        }
    }

    if (!disconnected)
    {
        enet_peer_reset(m_connection->peer);
        Logger::Info("Disconnection failed.");
    }

    Logger::Info("Disconnected from server.");
    enet_host_destroy(host);
    enet_deinitialize();
}

void ClientNetworkManager::ConnectToServer(std::string address, u16 port)
{
    if (enet_initialize() != 0)
    {
        Logger::Error("An error occurred while initializing ENet.");
    }

    ENetAddress enet_address = {0};
    enet_address_set_host_new(&enet_address, address.c_str());
    enet_address.port = port;

    host = enet_host_create(NULL, 1, 2, 0, 0);
    if (host == NULL)
    {
        Logger::Error("An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }

    ENetPeer *peer = enet_host_connect(host, &enet_address, 2, 0);
    if (peer == nullptr)
    {
        Logger::Error("No available peers for initiating an ENet connection.");
    }

    io_thread = new std::thread(PollNetwork, this);
    is_running = true;
}

void ClientNetworkManager::OnConnect(ENetPeer *peer)
{
    std::shared_ptr<Connection> connection = std::make_shared<Connection>();
    connection->peer = peer;
    connection->connected = true;
    connection->port = peer->address.port;
    connection->connection_id = peer->connectID;

    // enet_peer_timeout(event.peer, 2, 200, 500);

    connection->ip_address = GetAddress(peer);
    m_connection = connection;
    onConnect(connection, data);
    is_connected = true;
}

void ClientNetworkManager::OnDisconnect(ENetPeer *peer)
{
    is_connected = false;
    this->m_connection = nullptr;
}

void ClientNetworkManager::OnReceive(ENetPeer *peer, Message *message)
{
    onReceive(m_connection.get(), message);
}

} // namespace Novaland::Networking
