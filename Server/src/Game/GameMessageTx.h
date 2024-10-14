////////////////////////////////////////////////////////////////////////////////
// File:        GameMessageTx.h
// Author:      Bohumil Homola
// Date:        09/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/CharacterFramework.h"
#include "Networking/ServerNetworkManager.h"
#include "Player/ServerPlayer.h"
#include "Tick/TickManger.h"

namespace Novaland::Game
{

class GameMessageTx
{
  public:
    GameMessageTx();
    ~GameMessageTx();

    void GameStateUpdateMessage() const;
    void SendPlayerDisconnectedMessage(Player::ServerPlayer *player) const;
    void SendGameState(Player::ServerPlayer *ownPlayer) const;

  private:
    Container<Player::ServerPlayer> *player_container;
    Container<Character::CharacterFramework> *character_container;
    Networking::ServerNetworkManager *network_manager;
    TickManager *tick_manager;
};

} // namespace Novaland::Game
