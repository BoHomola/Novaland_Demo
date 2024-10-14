///////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageTx.h
// Author:      Bohumil Homola
// Date:        09/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Networking/ClientNetworkManager.h"
#include "Player/ClientPlayer.h"

namespace Novaland::Player
{

class PlayerMessageTx
{
  public:
    PlayerMessageTx();
    ~PlayerMessageTx();

  private:
    Container<ClientPlayer> *player_container;
    Networking::ClientNetworkManager *network_manager;
};
} // namespace Novaland::Player
