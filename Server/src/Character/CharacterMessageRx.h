////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.h
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterFramework.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/NetworkMessage.h"

namespace Novaland::Character
{

class CharacterMessageRx
{
  public:
    CharacterMessageRx();
    ~CharacterMessageRx();

    void HandleCharacterFireFinish(Networking::Message *message, Player::Player *player);
    void HandlePlayerMovementInput(Networking::Message *message, Player::Player *player);
    void HandlePlayerKeyInput(Networking::Message *message, Player::Player *player);

  private:
    void Initialize(MessageHandlerMap_t &message_handler);

  private:
    Container<CharacterFramework> *m_character_container;
};

} // namespace Novaland::Character
