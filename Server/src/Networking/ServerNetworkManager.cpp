////////////////////////////////////////////////////////////////////////////////
// File:        ServerNetworkManager.cpp
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ServerNetworkManager.h"
#include "DependencyInjector.h"
#include "Logger.h"

namespace Novaland::Networking
{

    ServerNetworkManager::ServerNetworkManager() : ANetworkManager()
    {
        send_queue = new SPSCQueue<SendMessageData>(200);
        Dependency::Register<ServerNetworkManager>(this);
    }

    ServerNetworkManager::~ServerNetworkManager()
    {
        delete send_queue;
    }

    void ServerNetworkManager::Send(Message *message, std::shared_ptr<Connection> connection, SendMode send_mode)
    {
        SendMessageData data;
        data.connections[0] = connection;
        data.connection_count = 1;
        data.message = message;
        data.send_mode = send_mode;

        auto result = send_queue->try_push(data);
        if (result == false)
        {
            Logger::Error("Failed to send message to queue.");
        }
    }

    void ServerNetworkManager::SendAll(Message *message, SendMode send_mode)
    {
        u32 index = 0;

        SendMessageData data;
        data.connection_count = connections.size();
        data.message = message;
        data.send_mode = send_mode;

        for (auto conn : connections)
        {
            data.connections[index] = conn.second;
            index++;
        }

        auto result = send_queue->try_push(data);
        if (result == false)
        {
            Logger::Error("Failed to send message to queue.");
        }
    }

    void ServerNetworkManager::SendAll(Message *message, std::shared_ptr<Connection> exemptConnection,
                                       SendMode send_mode)
    {
        u32 index = 0;

        SendMessageData data;
        data.connection_count = 0;
        data.message = message;
        data.send_mode = send_mode;

        for (auto conn : connections)
        {
            if (conn.second == exemptConnection)
            {
                continue;
            }

            data.connections[index] = conn.second;
            data.connection_count++;
            index++;
        }

        auto result = send_queue->try_push(data);
        if (result == false)
        {
            Logger::Error("Failed to send message to queue.");
        }
    }

    void ServerNetworkManager::SendMessage(const SendMessageData &send_message_data)
    {
        size_t total_size = sizeof(GameTag) + send_message_data.message->length;
        u32 flag = send_message_data.send_mode == SendMode::Reliable ? ENET_PACKET_FLAG_RELIABLE
                                                                     : ENET_PACKET_FLAG_UNSEQUENCED;
        ENetPacket *packet = enet_packet_create(send_message_data.message->GetRawData(), total_size, flag);
        for (int i = 0; i < send_message_data.connection_count; i++)
        {
            if (send_message_data.connections[i]->connected == false)
            {
                continue;
            }
            enet_peer_send(send_message_data.connections[i]->peer, 0, packet);
        }
        ReleaseOutcomingMessage(send_message_data.message);
    }

    void ServerNetworkManager::SendMessageQueue()
    {
        while (!send_queue->empty())
        {
            SendMessageData data = *send_queue->front();
            send_queue->pop();
            SendMessage(data);
        }
    }

    void ServerNetworkManager::StartNetworkServer(std::string address, u16 port)
    {
        if (enet_initialize() != 0)
        {
            Logger::Error("An error occurred while initializing ENet.");
        }

        ENetAddress enet_address = {0};
        enet_address.port = port;

        host = enet_host_create(&enet_address, 32, 2, 0, 0);
        if (host == nullptr)
        {
            Logger::Error("An error occurred while trying to create an ENet server host.");
        }

        is_running = true;
        io_thread = new std::thread(PollNetwork, this);
    }

    void ServerNetworkManager::OnConnect(ENetPeer *peer)
    {
        std::shared_ptr<Connection> connection = std::make_shared<Connection>();
        connection->peer = peer;
        connection->connected = true;
        connection->port = peer->address.port;
        connection->connection_id = peer->connectID;

        // enet_peer_timeout(event.peer, 2, 200, 500);

        connection->ip_address = GetAddress(peer);
        connections[peer] = connection;
        onConnect(connection, data);
    }

    void ServerNetworkManager::OnDisconnect(ENetPeer *peer)
    {
        std::shared_ptr<Connection> connection = connections[peer];
        if (connection == nullptr)
        {
            Logger::Error("Connection is null.");
            return;
        }

        onDisconnect(connection, data);
        connection->connected = false;
        connections.erase(peer);
    }

    void ServerNetworkManager::OnReceive(ENetPeer *peer, Message *message)
    {
        onReceive(connections[peer].get(), message);
    }

} // namespace Novaland::Networking
