////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageReceiver.h
// Author:      Bohumil Homola
// Date:        08/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterContainer.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Networking/NetworkMessage.h"

namespace Novaland::Character
{
class CharacterMessageRx
{
  public:
    CharacterMessageRx();
    ~CharacterMessageRx();

  private:
    void Initialize(MessageHandlerMap_t &message_handler);
    void HandleCharacterFireStart(Networking::Message *message, Player::Player *_);
    void HandleCharacterFireFinish(Networking::Message *message, Player::Player *player);
    void HandleCharacterHit(Networking::Message *message, Player::Player *player);

  private:
    CharacterContainer *m_character_container;
};
} // namespace Novaland::Character
