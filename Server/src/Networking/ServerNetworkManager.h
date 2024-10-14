////////////////////////////////////////////////////////////////////////////////
// File:        ServerNetworkManager.h
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Networking/Connection.h"
#include "Networking/NetworkManager.h"
#include "Networking/NetworkMessage.h"
#include "SpscQueue.h"
#include <memory>

namespace Novaland::Networking
{

struct SendMessageData
{
    Message *message;
    std::shared_ptr<Connection> connections[32];
    u16 connection_count;
    SendMode send_mode;
};

struct ServerNetworkManager : public ANetworkManager
{
  public:
    ServerNetworkManager();
    ~ServerNetworkManager();

    void Send(Message *message, std::shared_ptr<Connection> connection, SendMode send_mode);
    void SendAll(Message *message, SendMode send_mode);
    void SendAll(Message *message, std::shared_ptr<Connection> exemptConnection, SendMode send_mode);
    void StartNetworkServer(std::string address, u16 port);
    void Disconnect(std::shared_ptr<Connection> connection);

  private:
    void SendMessageQueue() override;
    void OnConnect(ENetPeer *) override;
    void OnDisconnect(ENetPeer *) override;
    void OnReceive(ENetPeer *, Message *) override;

  private:
    void SendMessage(const SendMessageData &send_message_data);

  private:
    std::unordered_map<ENetPeer *, std::shared_ptr<Connection>> connections;
    SPSCQueue<SendMessageData> *send_queue;
};

} // namespace Novaland::Networking
