////////////////////////////////////////////////////////////////////////////////
// File:        PlayerNetworkController.h
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "PlayerMessageTx.h"

namespace Novaland::Player
{

class PlayerNetworkController
{
  public:
    PlayerNetworkController();
    ~PlayerNetworkController();

  private:
    PlayerMessageTx *player_message_tx;
};

} // namespace Novaland::Player
