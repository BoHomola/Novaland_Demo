////////////////////////////////////////////////////////////////////////////////
// File:        PlayerCreator.h
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Lifetime/CharacterCreator.h"
#include "Player/PlayerContainer.h"
namespace Novaland::Player
{

struct PlayerInitilizationData
{
    u32 player_id = 0;
    u32 character_definition_id = 0;
    u32 character_id = 0;
    Physics::Transform transform;
    Physics::Velocity velocity;
    bool is_own = false;
};

class PlayerCreator
{
  public:
    PlayerCreator();
    ~PlayerCreator();

    Player *CreatePlayer(const PlayerInitilizationData &player_init_data);

  public:
    std::function<void(Player *player)> OnNewPlayerCreated;

  private:
    Character::CharacterCreator *character_creator;
    PlayerContainer *player_container;
};
} // namespace Novaland::Player
