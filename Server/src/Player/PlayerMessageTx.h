////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageTx.h
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

namespace Novaland::Player
{

class PlayerMessageTx
{
  public:
    PlayerMessageTx()
    {
        Dependency::Register<PlayerMessageTx>(this);
        player_container = Dependency::Get<Container<ServerPlayer>>();
        character_container = Dependency::Get<Container<Character::CharacterFramework>>();
        network_manager = Dependency::Get<Networking::ServerNetworkManager>();
    }
    ~PlayerMessageTx() = default;
    void NewPlayer(ServerPlayer *player);

  private:
    Container<ServerPlayer> *player_container;
    Container<Character::CharacterFramework> *character_container;
    Networking::ServerNetworkManager *network_manager;
};

} // namespace Novaland::Player
