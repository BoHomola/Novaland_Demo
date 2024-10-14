#pragma once

#include "DependencyInjector.h"
#include "GameTags.h"
#include "MessageBuffer.h"
#include "Networking/NetworkManager.h"
#include "Player/Player.h"

namespace Novaland
{
typedef std::function<void(Networking::Message *message, Player::Player *player)> MessageHandler_t;
typedef std::unordered_map<GameTag, MessageHandler_t> MessageHandlerMap_t;

struct MessageDispatcher
{
  public:
    MessageDispatcher()
    {
        Dependency::Register<MessageDispatcher>(this);
        network_server = Dependency::Get<Networking::ANetworkManager>();
    }

    ~MessageDispatcher()
    {
        for (MessageBuffer *message_buffer : message_buffers)
        {
            delete message_buffer;
        }
    }

    void ProcessMessages()
    {
        PROFILE_SCOPE
        for (MessageBuffer *message_buffer : message_buffers)
        {
            while (!message_buffer->messages.empty())
            {
                Networking::Message *message = *message_buffer->messages.front();
                message_buffer->messages.pop();
                GameTag tag = message->GetTag();
                auto handlerIt = message_handlers.find(tag);
                if (handlerIt != message_handlers.end())
                {
                    handlerIt->second(message, message_buffer->data);
                }
                else
                {
                    Logger::Error("Error: Unknown message tag received: {}", static_cast<u16>(tag));
                }

                network_server->ReleaseIncomingMessage(message);
            }
        }
    }

    MessageBuffer *InitNewMessageBuffer(Player::Player *data)
    {
        MessageBuffer *messageBuffer = new MessageBuffer();
        messageBuffer->data = data;
        message_buffers.push_back(messageBuffer);
        return messageBuffer;
    }

    void DestroyMessageBuffer(MessageBuffer *message_buffer)
    {
        auto it = std::find(message_buffers.begin(), message_buffers.end(), message_buffer);
        if (it != message_buffers.end())
        {
            message_buffers.erase(it);
            delete message_buffer;
        }
    }

  public:
    std::unordered_map<GameTag, MessageHandler_t> message_handlers;

  private:
    Networking::ANetworkManager *network_server;
    std::vector<MessageBuffer *> message_buffers;
};

} // namespace Novaland
