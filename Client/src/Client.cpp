////////////////////////////////////////////////////////////////////////////////
// File:        Client.cpp
// Author:      Bohumil Homola
// Date:        08/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Character/Character.h"
#include "DependencyInjector.h"
#include "Game/GameMessageRx.h"
#include "Input/Input.h"
#include "Logger.h"
#include "Networking/Connection.h"
#include "Networking/NetworkMessage.h"
#include "Physics/PhysicsWorld.h"
#include "Player/PlayerContainer.h"
#include "Player/PlayerMessageRx.h"
#include "Player/PlayerMessageTx.h"
#include "Player/PlayerNetworkController.h"
#include "Tick/TickManger.h"
#include "TimeUtils.h"

namespace Novaland
{
Client::Client()
{
    Logger::SetPrefix("Client");
    m_connection = nullptr;
    game_initialized = false;

    m_network_manager = new Networking::ClientNetworkManager();
    m_network_manager->onConnect = OnClientConnect;
    m_network_manager->onDisconnect = OnClientDisconnect;
    m_network_manager->onReceive = OnMessageReceive;
    m_network_manager->data = this;

    world = new Physics::PhysicsWorld();
    Dependency::Register<Physics::PhysicsWorld>(world);

    message_dispatcher = new MessageDispatcher();
    tick_manager = new TickManager();

    // Definition Providers
    character_definition_provider = new Definitions::CharacterDefinitionProvider();
    projectile_definition_provider = new Definitions::ProjectileDefinitionProvider();
    definition_parser = new Definitions::DefinitionParser();

    // Containers
    character_container = new Character::CharacterContainer();
    player_container = new Player::PlayerContainer();
    projectile_container = new Container<Projectile::ProjectileFramework>();

    // Creators
    character_creator = new Character::CharacterCreator();
    player_creator = new Player::PlayerCreator();
    projectile_creator = new Projectile::ProjectileCreator();

    // Destroyers
    character_destroyer = new Character::CharacterDestroyer();
    player_destroyer = new Player::PlayerDestroyer();
    projectile_destroyer = new Projectile::ProjectileDestroyer();

    // Controllers
    game_controller = new Game::GameController();

    // Transmitters
    player_message_tx = new Player::PlayerMessageTx();
    character_message_tx = new Character::CharacterMessageTx();

    // Network Controllers
    player_network_controller = new Player::PlayerNetworkController();

    // Receivers
    game_message_rx = new Game::GameMessageRx(m_game_state_updates);
    game_message_rx->on_game_initialized = [&]() {
        game_initialized = true;
        Logger::Info("Game initialized");
    };
    player_message_rx = new Player::PlayerMessageRx();
    character_message_rx = new Character::CharacterMessageRx();

    // Collision Handlers
    projectile_collision_handeler = new Projectile::ProjectileCollisionHandler();

    input_handler = new InputHandler(InputType::KEYBOARD);

    definition_parser->Parse("http://127.0.0.1:5555/get_client_definitions");
}

void Client::Connect(std::string ip_address, u32 port)
{
    m_network_manager->ConnectToServer(ip_address, port);
}

Client::~Client()
{
    m_network_manager->Disconnect();
}

void Client::Update(f32 delta_time)
{
    UpdateCharacters(delta_time);
    UpdateProjectiles(delta_time);
}

void Client::FixedUpdate()
{
    PROFILE_NEW_FRAME;
    PROFILE_SCOPE
    message_dispatcher->ProcessMessages();
    if (!game_initialized)
    {
        return;
    }

    if (m_game_state_updates.Empty())
    {
        Logger::Warn("Game message rx did not receive update");
    }
    else
    {
        game_controller->UpdateGameState(m_game_state_updates.Pop());
    }

    Input::Input input = input_handler->GetInput(character_container->own_character->m_character.rigidbody->GetAngle());
    Character::CharacterInput character_input = Character::CharacterInput{
        {input.movement_input.x, input.movement_input.y}, tick_manager->GetCurrentTick(), input.keys};
    character_container->own_character->m_input_component.ProcessInput(character_input);

    FixedUpdateCharacters();
    FixedUpdateProjectiles();

    world->UpdateWorld(TimeUtils::GetStepRate());

    PostFixedUpdateCharacters();
    PostFixedUpdateProjectiles();

    projectile_destroyer->Clean();
    tick_manager->IncreaseTick();
}

void Client::FixedUpdateCharacters()
{
    for (Character::CharacterFramework *character : character_container->GetAll())
    {
        character->FixedUpdate();
    }
}

void Client::FixedUpdateProjectiles()
{
    for (auto projectile : projectile_container->GetAll())
    {
        projectile->FixedUpdate();
    }
}

void Client::PostFixedUpdateCharacters()
{
    for (Character::CharacterFramework *const character : character_container->GetAll())
    {
        character->PostFixedUpdate();
    }
}

void Client::PostFixedUpdateProjectiles()
{
    for (Projectile::ProjectileFramework *const projectile : projectile_container->GetAll())
    {
        projectile->PostFixedUpdate();
    }
}

void Client::UpdateCharacters(f32 delta_time)
{
    for (Character::CharacterFramework *const character : character_container->GetAll())
    {
        character->Update(delta_time);
    }
}

void Client::UpdateProjectiles(f32 delta_time)
{
    for (Projectile::ProjectileFramework *const projectile : projectile_container->GetAll())
    {
        projectile->Update(delta_time);
    }
}

void OnClientConnect(std::shared_ptr<Networking::Connection> connection, void *data)
{
    Client *root = static_cast<Client *>(data);
    MessageBuffer *messageBuffer = root->message_dispatcher->InitNewMessageBuffer(nullptr);
    connection->data = messageBuffer;
    Logger::Info("Client connected to server. ID: {}", connection->connection_id);
    root->m_connection = connection;
}

void OnClientDisconnect(std::shared_ptr<Networking::Connection> connection, void *data)
{
    Client *root = static_cast<Client *>(data);
    Logger::Info("Client disconnected from server.");
    root->game_initialized = false;
}

void OnMessageReceive(Networking::Connection *connection, Networking::Message *message)
{
    MessageBuffer *messageBuffer = static_cast<MessageBuffer *>(connection->data);
    messageBuffer->messages.push(message);
}

} // namespace Novaland
