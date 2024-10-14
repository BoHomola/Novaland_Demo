////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.h
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "MessageDispatcher/MessageDispatcher.h"
#include "Player/PlayerNetworkController.h"

namespace Novaland::Player
{
class PlayerMessageRx
{
  public:
    PlayerMessageRx();
    ~PlayerMessageRx();

  private:
    void Initialize(MessageHandlerMap_t &message_handler);

  private:
    PlayerNetworkController *m_player_network_controller;
};
} // namespace Novaland::Player
