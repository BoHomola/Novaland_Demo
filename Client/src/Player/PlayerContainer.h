////////////////////////////////////////////////////////////////////////////////
// File:        PlayerContainer.h
// Author:      Bohumil Homola
// Date:        10/01/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "DependencyInjector.h"
#include "Player/ClientPlayer.h"

namespace Novaland::Player
{

class PlayerContainer : public Container<ClientPlayer>
{
  public:
    PlayerContainer()
    {
        Dependency::Register<PlayerContainer>(this);
        own_player = nullptr;
    }

    ~PlayerContainer()
    {
        Dependency::Unregister<PlayerContainer>();
    }

    ClientPlayer *own_player;
};

} // namespace Novaland::Player
