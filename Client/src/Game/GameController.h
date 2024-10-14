////////////////////////////////////////////////////////////////////////////////
// File:        GameController.h
// Author:      Bohumil Homola
// Date:        09/21/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterContainer.h"
#include "SerServer.h"
namespace Novaland::Game
{
class GameController
{

  public:
    GameController();

    void UpdateGameState(const Ser::GameStateUpdate &game_state_update);

  private:
    Character::CharacterContainer *character_container;
};
} // namespace Novaland::Game
