////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.h
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/NetworkMessage.h"
#include "Player/PlayerCreator.h"

namespace Novaland::Player
{
class PlayerMessageRx
{
  public:
    PlayerMessageRx();
    ~PlayerMessageRx();

    void OnNewPlayer(Networking::Message *message, Player *player);

  private:
    void Initialize(MessageHandlerMap_t &message_handler);

  private:
    PlayerCreator *player_creator;
};

} // namespace Novaland::Player
