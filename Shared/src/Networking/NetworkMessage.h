////////////////////////////////////////////////////////////////////////////////
// File:        NetworkMessage.hpp
// Author:      Bohumil Homola
// Date:        06/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "GameTags.h"
#include "NovalandCommon.h"

#ifndef NETWORK_MESSAGE_BUFFER_SIZE
#define NETWORK_MESSAGE_BUFFER_SIZE 4096
#endif

namespace Novaland::Networking
{

enum SendMode
{
    Reliable,
    Unreliable
};
class ANetworkManager;
struct Message
{
  public:
    Message();
    void SetTag(GameTag tag);
    const GameTag GetTag();
    void *GetMessagePtr();

  private:
    void *GetRawData();
    friend class ServerNetworkManager;
    friend class ClientNetworkManager;
    friend void PollNetwork(ANetworkManager *network_manager);

  public:
    u32 length;
    u8 channel;

  private:
    u8 data[NETWORK_MESSAGE_BUFFER_SIZE]{};
};

void SetTag(Message *message, GameTag tag);

} // namespace Novaland::Networking
