////////////////////////////////////////////////////////////////////////////////
// File:        GameMessageTx.cpp
// Author:      Bohumil Homola
// Date:        09/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "GameMessageTx.h"
#include "Character/CharacterFramework.h"
#include "Networking/NetworkMessage.h"
#include "Physics/Rigidbody.h"
#include "SerServer.h"

namespace Novaland::Game
{

GameMessageTx::GameMessageTx()
{
    Dependency::Register<GameMessageTx>(this);
    player_container = Dependency::Get<Container<Player::ServerPlayer>>();
    character_container = Dependency::Get<Container<Character::CharacterFramework>>();
    network_manager = Dependency::Get<Networking::ServerNetworkManager>();
    tick_manager = Dependency::Get<TickManager>();
}

GameMessageTx::~GameMessageTx()
{
}

void InitTransform(Ser::Transform &transform, Physics::Rigidbody *rigidBody)
{
    Physics::Transform rigidBodyData = rigidBody->GetTransform();
    Physics::Velocity rigidBodyVelocity = rigidBody->GetVelocity();

    transform.position.x = rigidBodyData.position.x;
    transform.position.y = rigidBodyData.position.y;

    transform.rotation = rigidBodyData.angle;
    transform.velocity.x = rigidBodyVelocity.linear_velocity.x;
    transform.velocity.y = rigidBodyVelocity.linear_velocity.y;

    transform.angularVelocity = rigidBodyVelocity.angular_velocity;
}

void GameMessageTx::GameStateUpdateMessage() const
{
    PROFILE_SCOPE
    auto players = player_container->GetAll();
    for (Player::ServerPlayer *player : players)
    {
        PROFILE_SCOPE
        auto message = network_manager->GetEmptyOutcomingMessage();
        auto [data, out] = zpp::bits::data_out();
        Ser::GameStateUpdate gameStateUpdate;
        gameStateUpdate.tick = tick_manager->GetCurrentTick();
        Character::CharacterFramework *server_character = character_container->Get(player->character_id);
        gameStateUpdate.clientTick =
            server_character->m_input_component.latest_input.tick; // weird way of geting last registered tick

        auto characters = character_container->GetAll();
        for (auto character_framework : characters)
        {
            Ser::CharacterEntity serializedCharacterEntity;
            serializedCharacterEntity.characterId = character_framework->id;
            InitTransform(serializedCharacterEntity.transform, character_framework->m_character.rigidbody);
            gameStateUpdate.characters.push_back(serializedCharacterEntity);
        }

        message->SetTag(GameTag::GAME_STATE_UPDATE);

        auto result = out(gameStateUpdate);
        memcpy(message->GetMessagePtr(), data.data(), data.size());
        message->length = data.size();

        network_manager->Send(message, player->player_connection, Networking::SendMode::Unreliable);
    }
}

void GameMessageTx::SendPlayerDisconnectedMessage(Player::ServerPlayer *player) const
{
    auto message = network_manager->GetEmptyOutcomingMessage();
    auto [data, out] = zpp::bits::data_out();
    Ser::PlayerId playerId{};
    playerId.id = player->id;

    message->SetTag(GameTag::PLAYER_DISCONNECTED);

    auto result = out(playerId);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    network_manager->SendAll(message, player->player_connection, Networking::SendMode::Reliable);
}

void GameMessageTx::SendGameState(Player::ServerPlayer *ownPlayer) const
{
    auto message = network_manager->GetEmptyOutcomingMessage();
    auto [data, out] = zpp::bits::data_out();

    Ser::GameStateSync gameState;
    gameState.firstTick = tick_manager->GetFirstTickUTC();
    gameState.ownPlayerId = ownPlayer->id;

    auto players = player_container->GetAll();
    for (auto player : players)
    {
        Ser::PlayerDefinition playerState;
        playerState.playerId = player->id;

        Ser::CharacterDefinition characterDefinition;
        characterDefinition.characterId = player->character_id;
        auto character_framework = character_container->Get(player->character_id);
        characterDefinition.characterDefinitionId = character_framework->definition->definition_id;
        InitTransform(characterDefinition.transform, character_framework->m_character.rigidbody);
        playerState.characterDefinition = characterDefinition;
        gameState.playerDefinitions.push_back(playerState);
    }

    message->SetTag(GameTag::GAME_STATE_SYNC);

    auto result = out(gameState);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    network_manager->Send(message, ownPlayer->player_connection, Networking::SendMode::Reliable);
}

} // namespace Novaland::Game
