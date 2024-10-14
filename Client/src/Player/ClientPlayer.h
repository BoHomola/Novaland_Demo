////////////////////////////////////////////////////////////////////////////////
// File:        ClientPlayer.hpp
// Author:      Bohumil Homola
// Date:        09/05/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <Player/Player.h>

namespace Novaland::Player
{
class ClientPlayer : public Player
{
  private:
    ClientPlayer(){};
    ~ClientPlayer(){};
    friend class PlayerCreator;
    friend class PlayerDestroyer;

  public:
    bool is_own;
};

} // namespace Novaland::Player
