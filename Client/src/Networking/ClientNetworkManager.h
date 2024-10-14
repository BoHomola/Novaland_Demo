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
namespace Novaland::Networking
{

struct SendMessageData
{
    Message *message;
    SendMode send_mode;
};

struct ClientNetworkManager : public ANetworkManager
{
  public:
    ClientNetworkManager();
    ~ClientNetworkManager() override;
    void Send(Message *message, SendMode send_mode);
    void ConnectToServer(std::string address, u16 port);
    void Disconnect();

  private:
    void SendMessageQueue() override;
    void OnConnect(ENetPeer *) override;
    void OnDisconnect(ENetPeer *) override;
    void OnReceive(ENetPeer *peer, Message *message) override;

  private:
    void SendMessage(const SendMessageData &send_message_data);

  public:
    bool is_connected;

  private:
    std::shared_ptr<Connection> m_connection;
    SPSCQueue<SendMessageData> *send_queue;
};

} // namespace Novaland::Networking
