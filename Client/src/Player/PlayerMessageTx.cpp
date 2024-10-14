////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageTx.cpp
// Author:      Bohumil Homola
// Date:        09/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerMessageTx.h"
#include "DependencyInjector.h"

namespace Novaland::Player
{
    PlayerMessageTx::PlayerMessageTx()
    {
        Dependency::Register<PlayerMessageTx>(this);
        player_container = Dependency::Get<Container<ClientPlayer>>();
        network_manager = Dependency::Get<Networking::ClientNetworkManager>();
    }

    PlayerMessageTx::~PlayerMessageTx()
    {
    }

} // namespace Novaland::Player
