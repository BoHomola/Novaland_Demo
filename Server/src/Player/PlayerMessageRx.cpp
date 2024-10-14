////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.cpp
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerMessageRx.h"
#include "DependencyInjector.h"
#include "MessageDispatcher/MessageDispatcher.h"

namespace Novaland::Player
{
    PlayerMessageRx::PlayerMessageRx()
    {
        Dependency::Register<PlayerMessageRx>(this);
        m_player_network_controller = Dependency::Get<PlayerNetworkController>();

        Initialize(Dependency::Get<MessageDispatcher>()->message_handlers);
    }

    void PlayerMessageRx::Initialize(MessageHandlerMap_t &message_handler)
    {
    }

    PlayerMessageRx::~PlayerMessageRx()
    {
    }

} // namespace Novaland::Player
