////////////////////////////////////////////////////////////////////////////////
// File:        PlayerDestroyer.h
// Author:      Bohumil Homola
// Date:        09/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Lifetime/CharacterDestroyer.h"
#include "ClientPlayer.h"

namespace Novaland::Player
{
class PlayerDestroyer
{
  public:
    PlayerDestroyer();
    ~PlayerDestroyer();

    void DestroyPlayer(u32 playerId);

  private:
    Character::CharacterDestroyer *character_destroyer;
    Container<ClientPlayer> *player_container;
};
} // namespace Novaland::Player
