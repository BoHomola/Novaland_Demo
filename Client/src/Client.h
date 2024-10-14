////////////////////////////////////////////////////////////////////////////////
// File:        Client.h
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterContainer.h"
#include "Character/CharacterMessageRx.h"
#include "Character/CharacterMessageTx.h"
#include "Character/Lifetime/CharacterDestroyer.h"
#include "Definitions/DefinitionParser.h"
#include "Definitions/ProjectileDefinitionProvider.h"
#include "Game/GameController.h"
#include "Game/GameMessageRx.h"
#include "Input/InputHandler.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/ClientNetworkManager.h"
#include "Networking/Connection.h"
#include "Networking/NetworkMessage.h"
#include "NovalandCommon.h"
#include "OverwriteBuffer.h"
#include "Player/PlayerContainer.h"
#include "Player/PlayerMessageRx.h"
#include "Player/PlayerMessageTx.h"
#include "Player/PlayerNetworkController.h"
#include "Projectile/Lifetime/ProjectileCreator.h"
#include "Projectile/Lifetime/ProjectileDestroyer.h"
#include "Projectile/ProjectileCollisionHandler.h"
#include "Tick/TickManger.h"

namespace Novaland
{

class Client
{

  public:
    Client();
    void Update(f32 delta_time);
    void FixedUpdate();
    void Connect(std::string ip_address, u32 port);
    ~Client();

  private:
    void FixedUpdateCharacters();
    void FixedUpdateProjectiles();
    void PostFixedUpdateCharacters();
    void PostFixedUpdateProjectiles();
    void UpdateCharacters(f32 delta_time);
    void UpdateProjectiles(f32 delta_time);

  public:
    // Containers
    Character::CharacterContainer *character_container;
    Player::PlayerContainer *player_container;
    Container<Projectile::ProjectileFramework> *projectile_container;

    // Controllers
    Game::GameController *game_controller;

    // Network Controllers
    Player::PlayerNetworkController *player_network_controller;

    // Creators
    Character::CharacterCreator *character_creator;
    Player::PlayerCreator *player_creator;
    Projectile::ProjectileCreator *projectile_creator;

    // Destroyers
    Character::CharacterDestroyer *character_destroyer;
    Player::PlayerDestroyer *player_destroyer;
    Projectile::ProjectileDestroyer *projectile_destroyer;

    // Receivers
    Player::PlayerMessageRx *player_message_rx;
    Game::GameMessageRx *game_message_rx;
    Character::CharacterMessageRx *character_message_rx;

    // Transmitters
    Player::PlayerMessageTx *player_message_tx;
    Character::CharacterMessageTx *character_message_tx;

    // Definition Providers
    Definitions::DefinitionParser *definition_parser;
    Definitions::CharacterDefinitionProvider *character_definition_provider;
    Definitions::ProjectileDefinitionProvider *projectile_definition_provider;

    // Collision Handlers
    Projectile::ProjectileCollisionHandler *projectile_collision_handeler;

    Physics::PhysicsWorld *world;
    Physics::PhysicsWorld *simulation_world;
    std::shared_ptr<Networking::Connection> m_connection;
    OverwriteBuffer<Ser::GameStateUpdate> m_game_state_updates{2};

    InputHandler *input_handler;
    Networking::ClientNetworkManager *m_network_manager;
    Character::CharacterReconciliationComponent *character_reconciliation;
    Character::CharacterSnapshotQueue *character_snapshot_queue;
    bool game_initialized;
    Player::Player *player;
    MessageDispatcher *message_dispatcher;
    TickManager *tick_manager;
};

void OnClientConnect(std::shared_ptr<Networking::Connection> connection, void *data);
void OnClientDisconnect(std::shared_ptr<Networking::Connection> connection, void *data);
void OnMessageReceive(Networking::Connection *connection, Networking::Message *message);
} // namespace Novaland
