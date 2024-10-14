////////////////////////////////////////////////////////////////////////////////
// File:        PlayerCreator.cpp
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerCreator.h"
#include "MessageDispatcher/MessageDispatcher.h"

namespace Novaland::Player
{

PlayerCreator::PlayerCreator()
{
    Dependency::Register<PlayerCreator>(this);
    character_creator = Dependency::Get<Character::CharacterCreator>();
    player_container = Dependency::Get<Container<ServerPlayer>>();
    message_dispatcher = Dependency::Get<MessageDispatcher>();
}

PlayerCreator::~PlayerCreator()
{
}

ServerPlayer *PlayerCreator::CreatePlayer(std::shared_ptr<Networking::Connection> connection)
{
    ServerPlayer *player = new ServerPlayer;
    player->id = connection->connection_id;
    player->player_connection = connection;
    player->client_tick = 0;
    // TODO: Do not forget to set proper definiton id
    player->character_id = character_creator->CreateCharacter(0)->id;
    auto message_buffer = message_dispatcher->InitNewMessageBuffer(player);
    connection->data = message_buffer;
    player_container->Add(player);
    return player;
}

} // namespace Novaland::Player
