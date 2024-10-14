////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageBuffer.h
// Author:      Bohumil Homola
// Date:        08/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Networking/NetworkMessage.h"
#include "Player/Player.h"
#include "SpscQueue.h"

namespace Novaland
{
struct MessageBuffer
{
  public:
    MessageBuffer() : messages(100)
    {
    }

  public:
    SPSCQueue<Novaland::Networking::Message *> messages;
    Player::Player *data;
};
} // namespace Novaland
