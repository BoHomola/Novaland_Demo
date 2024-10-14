////////////////////////////////////////////////////////////////////////////////
// File:        PlayerDestroyer.cpp
// Author:      Bohumil Homola
// Date:        09/09/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerDestroyer.h"
#include "DependencyInjector.h"

namespace Novaland::Player
{

PlayerDestroyer::PlayerDestroyer()
{
    Dependency::Register<PlayerDestroyer>(this);
    character_destroyer = Dependency::Get<Character::CharacterDestroyer>();
    player_container = Dependency::Get<Container<ServerPlayer>>();
    message_dispatcher = Dependency::Get<MessageDispatcher>();
}

void PlayerDestroyer::DestroyPlayer(u32 playerId)
{
    auto player = player_container->Get(playerId);
    if (player == nullptr)
    {
        return;
    }

    character_destroyer->DestroyCharacter(player->character_id);
    message_dispatcher->DestroyMessageBuffer(static_cast<MessageBuffer *>(player->player_connection->data));
    player_container->Remove(playerId);
    delete player;
}

} // namespace Novaland::Player
