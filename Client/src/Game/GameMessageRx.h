////////////////////////////////////////////////////////////////////////////////
// File:        GameMessageRx.h
// Author:      Bohumil Homola
// Date:        08/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "OverwriteBuffer.h"
#include "Player/PlayerCreator.h"
#include "Player/PlayerDestroyer.h"
#include "SerServer.h"

namespace Novaland::Game
{
class GameMessageRx
{

  public:
    GameMessageRx(OverwriteBuffer<Ser::GameStateUpdate> &game_state_updates);
    ~GameMessageRx();

    void OnGameStateUpdate(Networking::Message *message, Player::Player *_);
    void OnGameStateSync(Networking::Message *message, Player::Player *_);
    void OnPlayerDisconnected(Networking::Message *message, Player::Player *_);

  private:
    void Initialize(MessageHandlerMap_t &message_handler);

  public:
    std::function<void()> on_game_initialized;

  private:
    OverwriteBuffer<Ser::GameStateUpdate> &game_state_updates;
    Container<Player::ClientPlayer> *player_container;
    Container<Character::CharacterFramework> *character_container;
    Player::PlayerCreator *player_creator;
    Player::PlayerDestroyer *player_destroyer;
};

} // namespace Novaland::Game
