////////////////////////////////////////////////////////////////////////////////
// File:        GameMessageRx.cpp
// Author:      Bohumil Homola
// Date:        08/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "GameMessageRx.h"
#include "DependencyInjector.h"
#include "GameTags.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Physics/Rigidbody.h"
#include "SerServer.h"

namespace Novaland::Game
{

GameMessageRx::GameMessageRx(OverwriteBuffer<Ser::GameStateUpdate> &game_state_updates)
    : game_state_updates(game_state_updates)
{
    Dependency::Register<GameMessageRx>(this);
    player_container = Dependency::Get<Container<Player::ClientPlayer>>();
    player_creator = Dependency::Get<Player::PlayerCreator>();
    character_container = Dependency::Get<Container<Character::CharacterFramework>>();
    player_destroyer = Dependency::Get<Player::PlayerDestroyer>();

    Initialize(Dependency::Get<MessageDispatcher>()->message_handlers);
}

void GameMessageRx::Initialize(MessageHandlerMap_t &message_handler)
{
    message_handler.emplace(GameTag::GAME_STATE_UPDATE, [this](Networking::Message *message, Player::Player *player) {
        this->OnGameStateUpdate(message, player);
    });
    message_handler.emplace(GameTag::GAME_STATE_SYNC, [this](Networking::Message *message, Player::Player *player) {
        this->OnGameStateSync(message, player);
    });
    message_handler.emplace(GameTag::PLAYER_DISCONNECTED, [this](Networking::Message *message, Player::Player *player) {
        this->OnPlayerDisconnected(message, player);
    });
}

void GameMessageRx::OnGameStateUpdate(Networking::Message *message, Player::Player *_)
{
    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);
    Ser::GameStateUpdate gameStateUpdate;
    auto result = in(gameStateUpdate);
    game_state_updates.Push(gameStateUpdate);
}

void GameMessageRx::OnGameStateSync(Networking::Message *message, Player::Player *_)
{

    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);

    Ser::GameStateSync gameStateSync;
    auto result = in(gameStateSync);

    for (Ser::PlayerDefinition playerDefinition : gameStateSync.playerDefinitions)
    {
        Player::PlayerInitilizationData player_init_data;
        player_init_data.player_id = playerDefinition.playerId;
        player_init_data.character_definition_id = playerDefinition.characterDefinition.characterDefinitionId;
        player_init_data.character_id = playerDefinition.characterDefinition.characterId;
        auto transform = playerDefinition.characterDefinition.transform;

        Vec2 position = {transform.position.x, transform.position.y};
        Vec2 linear_velocity = {transform.velocity.x, transform.velocity.y};

        player_init_data.transform = {position, transform.rotation};
        player_init_data.velocity = {linear_velocity, transform.angularVelocity};

        player_init_data.is_own = playerDefinition.playerId == gameStateSync.ownPlayerId;
        player_creator->CreatePlayer(player_init_data);
    }

    on_game_initialized();
}

void GameMessageRx::OnPlayerDisconnected(Networking::Message *message, Player::Player *_)
{
    auto [data, in] = zpp::bits::data_in();
    data.resize(message->length);
    memcpy(data.data(), message->GetMessagePtr(), message->length);
    Ser::PlayerId playerDisconnected;
    auto result = in(playerDisconnected);

    player_destroyer->DestroyPlayer(playerDisconnected.id);
}

GameMessageRx::~GameMessageRx()
{
}

} // namespace Novaland::Game
