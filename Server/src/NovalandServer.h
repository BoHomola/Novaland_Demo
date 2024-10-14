#pragma once
#include "Character/CharacterCollisionHandler.h"
#include "Character/CharacterMessageRx.h"
#include "Definitions/DefinitionParser.h"
#include "Definitions/ProjectileDefinitionProvider.h"
#include "Game/GameMessageTx.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/NetworkMessage.h"
#include "Networking/ServerNetworkManager.h"
#include "NovalandCommon.h"
#include "Player/PlayerCreator.h"
#include "Player/PlayerDestroyer.h"
#include "Player/PlayerMessageRx.h"
#include "Player/PlayerMessageTx.h"
#include "Player/PlayerNetworkController.h"
#include "Player/ServerPlayer.h"
#include "Projectile/Lifetime/ProjectileCreator.h"
#include "Tick/TickManger.h"

namespace Novaland
{
struct NovalandServer
{
  public:
    NovalandServer(std::string ip_address, u16 port, u32 update_interval);
    ~NovalandServer();
    void StartServer();
    void StopServer();
    void FixedUpdate();

  private:
    void FixedUpdateCharacters();
    void FixedUpdateProjectiles();

  public:
    std::string address_ip;
    u16 port;
    // Containers
    Container<Player::ServerPlayer> *player_container;
    Container<Character::CharacterFramework> *character_container;
    Container<Projectile::ProjectileFramework> *projectile_container;
    // NetworkControllers
    Player::PlayerNetworkController *player_network_controller;
    // Creators
    Player::PlayerCreator *player_creator;
    Character::CharacterCreator *character_creator;
    Projectile::ProjectileCreator *projectile_creator;
    // Destroyers
    Character::CharacterDestroyer *character_destroyer;
    Player::PlayerDestroyer *player_destroyer;
    Projectile::ProjectileDestroyer *projectile_destroyer;

    // Receivers
    Player::PlayerMessageRx *player_message_rx;
    Character::CharacterMessageRx *character_message_rx;
    // Transmitters
    Game::GameMessageTx *game_message_tx;
    Player::PlayerMessageTx *player_message_tx;
    Character::CharacterMessageTx *character_message_tx;
    // Definition Providers
    Definitions::CharacterDefinitionProvider *character_definition_provider;
    Definitions::ProjectileDefinitionProvider *projectile_definition_provider;
    Definitions::DefinitionParser *definition_parser;
    // Collision Handelers
    Character::CharacterCollisionHandler *character_collision_handler;

    Physics::PhysicsWorld *p_world;

  private:
    Networking::ServerNetworkManager *networking_server;
    u32 update_interval;
    bool is_running;
    MessageDispatcher *message_dispatcher;
    TickManager *tick_manager;
    std::mutex m_mutex;

    friend void OnPlayerConnect(std::shared_ptr<Networking::Connection> connection, void *data);
    friend void OnPlayerDisconnect(std::shared_ptr<Networking::Connection> connection, void *data);
};

void OnPlayerConnect(std::shared_ptr<Networking::Connection> connection, void *data);
void OnPlayerDisconnect(std::shared_ptr<Networking::Connection> connection, void *data);
void OnMessageReceive(Networking::Connection *connection, Networking::Message *message);

} // namespace Novaland
