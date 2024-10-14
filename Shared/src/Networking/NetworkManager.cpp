///////////////////////////////////////////////////////////////////////////////
// File:        NetworkManager.cpp
// Author:      Bohumil Homola
// Date:        06/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NetworkManager.h"
#include "DependencyInjector.h"
#include "Logger.h"
#include "enet.h"
#include <cstring>
#include <memory>
#include <string>

namespace Novaland::Networking
{

    ANetworkManager::ANetworkManager()
    {
        incoming_message_pool = new ObjectPool<Message>(100);
        outcoming_message_pool = new ObjectPool<Message>(100);
        Dependency::Register<ANetworkManager>(this);
    }

    void PollNetwork(ANetworkManager *network_manager)
    {
        ENetEvent event;
        while (network_manager->is_running)
        {
            network_manager->SendMessageQueue();
            enet_host_flush(network_manager->host);

            while (enet_host_service(network_manager->host, &event, 2) > 0)
            {

                switch (event.type)
                {
                case ENET_EVENT_TYPE_CONNECT: {
                    network_manager->OnConnect(event.peer);
                    break;
                }

                case ENET_EVENT_TYPE_RECEIVE: {
                    Message *message = network_manager->GetEmptyIncomingMessage();
                    memcpy(message->GetRawData(), event.packet->data, event.packet->dataLength);
                    message->length = event.packet->dataLength - sizeof(GameTag);
                    message->channel = event.channelID;
                    network_manager->OnReceive(event.peer, message);

                    enet_packet_destroy(event.packet);
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT: {
                    network_manager->OnDisconnect(event.peer);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT: {
                    network_manager->OnDisconnect(event.peer);
                    break;
                }
                case ENET_EVENT_TYPE_NONE:
                    break;
                }
            }
        }
    }

    ANetworkManager::~ANetworkManager()
    {
        is_running = false;
        io_thread->join();
        enet_deinitialize();
        enet_host_destroy(host);
        delete io_thread;
        delete incoming_message_pool;
        Logger::Info("Network manager destroyed.");
    }

    void ANetworkManager::ReleaseIncomingMessage(Message *message)
    {
        incoming_message_pool->Release(message);
    }

    void ANetworkManager::ReleaseOutcomingMessage(Message *message)
    {
        outcoming_message_pool->Release(message);
    }

    Message *ANetworkManager::GetEmptyOutcomingMessage()
    {

        Message *message = outcoming_message_pool->Get();
        return message;
    }

    Message *ANetworkManager::GetEmptyIncomingMessage()
    {

        Message *message = incoming_message_pool->Get();
        return message;
    }

    std::string ANetworkManager::GetAddress(ENetPeer *peer)
    {
        char buffer[INET6_ADDRSTRLEN];
        enet_address_get_host_ip(&peer->address, buffer, INET6_ADDRSTRLEN);
        std::string address = std::string(buffer);
        if (address.substr(0, 7) == "::ffff:")
        {
            std::size_t pos = address.rfind(':');
            if (pos != std::string::npos)
            {
                address = address.substr(7, pos - 7); // Extract just the IPv4 address.
            }
            else
            {
                address = address.substr(7); // If no port is found, take the whole address.
            }
        }
        return std::move(address);
    }
} // namespace Novaland::Networking
