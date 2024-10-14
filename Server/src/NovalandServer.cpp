#include "NovalandServer.h"
#include "Definitions/CharacterDefinitionProvider.h"
#include "DependencyInjector.h"
#include "Game/GameMessageTx.h"
#include "Logger.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/NetworkMessage.h"
#include "Physics/PhysicsWorld.h"
#include "Player/PlayerCreator.h"
#include "Player/PlayerNetworkController.h"
#include "TimeUtils.h"
#include <memory>
#include <mutex>

namespace Novaland
{

NovalandServer::NovalandServer(std::string ip_address, u16 port, u32 update_interval)
{
    this->address_ip = ip_address;
    this->port = port;
    this->update_interval = update_interval;

    networking_server = new Networking::ServerNetworkManager();
    networking_server->onConnect = &OnPlayerConnect;
    networking_server->onDisconnect = &OnPlayerDisconnect;
    networking_server->onReceive = &OnMessageReceive;
    networking_server->data = this;

    p_world = new Physics::PhysicsWorld();
    Dependency::Register<Physics::PhysicsWorld>(p_world);

    tick_manager = new TickManager();

    // Definition Providers
    character_definition_provider = new Definitions::CharacterDefinitionProvider();
    projectile_definition_provider = new Definitions::ProjectileDefinitionProvider();
    definition_parser = new Definitions::DefinitionParser();

    // Containers
    character_container = new Container<Character::CharacterFramework>();
    player_container = new Container<Player::ServerPlayer>();
    projectile_container = new Container<Projectile::ProjectileFramework>();

    message_dispatcher = new MessageDispatcher();

    // Creators
    character_creator = new Character::CharacterCreator();
    player_creator = new Player::PlayerCreator();
    projectile_creator = new Projectile::ProjectileCreator();

    // Destroyers
    character_destroyer = new Character::CharacterDestroyer();
    player_destroyer = new Player::PlayerDestroyer();
    projectile_destroyer = new Projectile::ProjectileDestroyer();

    // Transmitters
    game_message_tx = new Game::GameMessageTx();
    player_message_tx = new Player::PlayerMessageTx();
    character_message_tx = new Character::CharacterMessageTx();

    // Network Controllers
    player_network_controller = new Player::PlayerNetworkController();

    // Receivers
    player_message_rx = new Player::PlayerMessageRx();
    character_message_rx = new Character::CharacterMessageRx();

    // Collision Handelers
    character_collision_handler = new Character::CharacterCollisionHandler();

    //temp hardcoded url for obtaining definitions
   definition_parser->Parse("http://127.0.0.1:5555/get_server_definitions");
}

void OnPlayerConnect(std::shared_ptr<Networking::Connection> connection, void *data)
{
    NovalandServer *root = static_cast<NovalandServer *>(data);
    root->m_mutex.lock();
    Player::ServerPlayer *newPlayer = root->player_creator->CreatePlayer(connection);
    Logger::Info("New connection {0}:{1}", connection->ip_address, connection->port);

    root->player_message_tx->NewPlayer(newPlayer);
    root->game_message_tx->SendGameState(newPlayer);
    root->m_mutex.unlock();
}

void OnPlayerDisconnect(std::shared_ptr<Networking::Connection> connection, void *data)
{
    NovalandServer *root = static_cast<NovalandServer *>(data);

    root->m_mutex.lock();
    Player::ServerPlayer *player = root->player_container->Get(connection->connection_id);
    if (player == nullptr)
    {
        Logger::Error("Trying to lose connection of a player that doesn't exist");
        return;
    }
    root->game_message_tx->SendPlayerDisconnectedMessage(player);
    root->player_destroyer->DestroyPlayer(player->id);

    Logger::Info("Connection Lost {0}:{1}", connection->ip_address, connection->port);
    root->m_mutex.unlock();
}

void OnMessageReceive(Networking::Connection *connection, Networking::Message *message)
{
    MessageBuffer *messageBuffer = static_cast<MessageBuffer *>(connection->data);
    messageBuffer->messages.push(message);
}

void NovalandServer::FixedUpdate()
{
    PROFILE_NEW_FRAME
    PROFILE_SCOPE
    m_mutex.lock();
    message_dispatcher->ProcessMessages();

    FixedUpdateCharacters();
    FixedUpdateProjectiles();

    f32 timeStamp = 1.0f / update_interval;
    p_world->UpdateWorld(timeStamp);

    game_message_tx->GameStateUpdateMessage();

    projectile_destroyer->Clean();

    tick_manager->IncreaseTick();
    m_mutex.unlock();
}

void NovalandServer::StartServer()
{
    networking_server->StartNetworkServer(address_ip, port);
    is_running = true;

    const u32 milliseconds_in_second = 1000;
    auto tick_duration = std::chrono::milliseconds(milliseconds_in_second / update_interval);
    auto next_tick_time = std::chrono::steady_clock::now() + tick_duration;
    tick_manager->SetFirstTickUTC(TimeUtils::GetUtcNow());
    tick_manager->SetDeltaTime(1.0f / (f32)update_interval);

    while (is_running)
    {
        FixedUpdate();

        auto current_time = std::chrono::steady_clock::now();

        if (current_time < next_tick_time)
        {

            std::this_thread::sleep_until(next_tick_time);
            next_tick_time += tick_duration;
        }
        else
        {
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - next_tick_time);
            next_tick_time = current_time + tick_duration;
            Logger::Warn("Server cannot keep up with the tick rate. It is lagging behind by {0} ms", diff.count());
        }
    }
}

void NovalandServer::StopServer()
{
    is_running = false;
    delete networking_server;
}

void NovalandServer::FixedUpdateCharacters()
{
    for (Character::CharacterFramework *character : character_container->GetAll())
    {
        character->FixedUpdate();
    }
}

void NovalandServer::FixedUpdateProjectiles()
{
    for (auto projectile : projectile_container->GetAll())
    {
        projectile->FixedUpdate();
    }
}

NovalandServer::~NovalandServer()
{
    delete character_definition_provider;
    delete projectile_definition_provider;
    delete definition_parser;

    delete character_container;
    delete player_container;
    delete projectile_container;

    delete message_dispatcher;

    delete character_creator;
    delete player_creator;
    delete projectile_creator;

    delete character_destroyer;
    delete player_destroyer;
    delete projectile_destroyer;

    delete game_message_tx;
    delete player_message_tx;
    delete character_message_tx;

    delete player_network_controller;

    delete player_message_rx;
    delete character_message_rx;

    delete character_collision_handler;

    delete p_world;
    delete tick_manager;
}

} // namespace Novaland
