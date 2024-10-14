///////////////////////////////////////////////////////////////////////////////
// File:        PlayerCreator.cpp
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerCreator.h"
#include "DependencyInjector.h"
#include "Player/PlayerContainer.h"

namespace Novaland::Player
{
PlayerCreator::PlayerCreator()
{
    Dependency::Register<PlayerCreator>(this);
    character_creator = Dependency::Get<Character::CharacterCreator>();
    player_container = Dependency::Get<PlayerContainer>();
}

PlayerCreator::~PlayerCreator()
{
}

Player *PlayerCreator::CreatePlayer(const PlayerInitilizationData &player_init_data)
{
    ClientPlayer *player = new ClientPlayer;
    player->id = player_init_data.player_id;
    player->is_own = player_init_data.is_own;
    // do not forget to pass definiton ID
    player->character_id = character_creator
                               ->CreateCharacter(player_init_data.character_id,
                                                 player_init_data.character_definition_id, player_init_data.is_own)
                               ->id;
    player_container->Add(player);
    if (player->is_own)
    {
        player_container->own_player = player;
    }

    if (OnNewPlayerCreated)
    {
        OnNewPlayerCreated(player);
    }
    return player;
}
} // namespace Novaland::Player
