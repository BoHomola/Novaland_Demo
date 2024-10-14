////////////////////////////////////////////////////////////////////////////////
// File:        NetworkManager.hpp
// Author:      Bohumil Homola
// Date:        06/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Connection.h"
#include "NetworkMessage.h"
#include "ObjectPool.h"
#include <enet.h>
#include <functional>
#include <thread>

namespace Novaland::Networking
{

struct ANetworkManager
{
  public:
    ANetworkManager();
    virtual ~ANetworkManager();
    Message *GetEmptyOutcomingMessage();
    void ReleaseIncomingMessage(Message *message);

  private:
    virtual void SendMessageQueue() = 0;
    virtual void OnConnect(ENetPeer *) = 0;
    virtual void OnDisconnect(ENetPeer *) = 0;
    virtual void OnReceive(ENetPeer *, Message *) = 0;

  public:
    void *data;
    std::function<void(std::shared_ptr<Connection>, void *data)> onConnect;
    std::function<void(std::shared_ptr<Connection>, void *data)> onDisconnect;
    std::function<void(Connection *, Message *)> onReceive;

  protected:
    std::string GetAddress(ENetPeer *peer);
    Message *GetEmptyIncomingMessage();
    void ReleaseOutcomingMessage(Message *message);

  protected:
    bool is_running;
    ENetHost *host;
    std::thread *io_thread;

  private:
    ObjectPool<Message> *incoming_message_pool;
    ObjectPool<Message> *outcoming_message_pool;

    friend void PollNetwork(ANetworkManager *network_manager);
};

void PollNetwork(ANetworkManager *network_server);

} // namespace Novaland::Networking
