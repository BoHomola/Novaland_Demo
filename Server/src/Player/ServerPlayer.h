////////////////////////////////////////////////////////////////////////////////
// File:        ClientPlayer.hpp
// Author:      Bohumil Homola
// Date:        09/05/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Networking/Connection.h"
#include <Player/Player.h>

namespace Novaland::Player
{
class ServerPlayer : public Player
{
  private:
    ServerPlayer(){};
    ~ServerPlayer(){};
    friend class PlayerCreator;
    friend class PlayerDestroyer;

  public:
    u32 client_tick;
    std::shared_ptr<Networking::Connection> player_connection;
};

} // namespace Novaland::Player
