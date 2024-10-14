////////////////////////////////////////////////////////////////////////////////
// File:        PlayerCreator.h
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Lifetime/CharacterCreator.h"
#include "MessageDispatcher/MessageDispatcher.h"
#include "Player/ServerPlayer.h"
namespace Novaland::Player
{

struct PlayerInitilizationData
{
    u32 player_id;
    u32 character_definition_id;
    u32 character_id;
    Physics::Transform transform;
};

class PlayerCreator
{
  public:
    PlayerCreator();
    ~PlayerCreator();

    ServerPlayer *CreatePlayer(std::shared_ptr<Networking::Connection> connection);

  private:
    Character::CharacterCreator *character_creator;
    Container<ServerPlayer> *player_container;
    MessageDispatcher *message_dispatcher;
};

} // namespace Novaland::Player
