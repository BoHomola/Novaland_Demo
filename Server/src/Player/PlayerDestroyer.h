////////////////////////////////////////////////////////////////////////////////
// File:        PlayerDestroyer.h
// Author:      Bohumil Homola
// Date:        09/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/Lifetime/CharacterDestroyer.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Player/ServerPlayer.h"

namespace Novaland::Player
{

class PlayerDestroyer
{
  public:
    PlayerDestroyer();

    void DestroyPlayer(u32 playerId);

  private:
    Container<ServerPlayer> *player_container;
    Character::CharacterDestroyer *character_destroyer;
    MessageDispatcher *message_dispatcher;
};
} // namespace Novaland::Player
