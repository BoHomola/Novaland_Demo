////////////////////////////////////////////////////////////////////////////////
// File:        PlayerNetworkController.cpp
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerNetworkController.h"
#include "DependencyInjector.h"

namespace Novaland::Player
{
    PlayerNetworkController::PlayerNetworkController()
    {
        Dependency::Register<PlayerNetworkController>(this);
    }
    PlayerNetworkController::~PlayerNetworkController()
    {
        Dependency::Unregister<PlayerNetworkController>();
    }
} // namespace Novaland::Player
