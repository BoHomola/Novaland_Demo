////////////////////////////////////////////////////////////////////////////////
// File:        CharacterMessageTx.h
// Author:      Bohumil Homola
// Date:        09/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Components/CharacterInputComponent/CharacterInput.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/ClientNetworkManager.h"
#include "Tick/TickManger.h"

namespace Novaland::Character
{

class CharacterMessageTx
{
  public:
    CharacterMessageTx();
    ~CharacterMessageTx();
    void Initialize(MessageHandlerMap_t &message_handler);
    void SendCharacterInput(CharacterInput &input);

  private:
    TickManager *tick_manager;
    Networking::ClientNetworkManager *network_manager;
};
} // namespace Novaland::Character
