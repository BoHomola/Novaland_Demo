////////////////////////////////////////////////////////////////////////////////
// File:        PlayerDestroyer.cpp
// Author:      Bohumil Homola
// Date:        09/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerDestroyer.h"

namespace Novaland::Player
{
    PlayerDestroyer::PlayerDestroyer()
    {
        Dependency::Register<PlayerDestroyer>(this);
        character_destroyer = Dependency::Get<Character::CharacterDestroyer>();
        player_container = Dependency::Get<Container<ClientPlayer>>();
    }

    PlayerDestroyer::~PlayerDestroyer()
    {
        Dependency::Unregister<PlayerDestroyer>();
    }

    void PlayerDestroyer::DestroyPlayer(u32 playerId)
    {
        auto player = player_container->Get(playerId);
        if (player == nullptr)
        {
            return;
        }
        character_destroyer->DestroyCharacter(player->character_id);
        player_container->Remove(playerId);
        delete player;
    }
} // namespace Novaland::Player
