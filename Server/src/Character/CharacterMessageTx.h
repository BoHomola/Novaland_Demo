////////////////////////////////////////////////////////////////////////////////
// File:        CharacterMessageTx.h
// Author:      Bohumil Homola
// Date:        10/01/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Character.h"
#include "Networking/ServerNetworkManager.h"
#include "Physics/CollisionListener.h"
#include "Projectile/ProjectileFramework.h"
#include "Tick/TickManger.h"

namespace Novaland::Character
{

class CharacterMessageTx
{
  public:
    CharacterMessageTx();
    ~CharacterMessageTx();

    void SendCharacterStartFireMessage(u32 character_id);
    void SendCharacterFinishFireMessage(Character *character, Projectile::ProjectileFramework *projectile,
                                        const Vec2 &start_pos, f32 dir);
    void SendCharacterHitMessage(Character *character, Projectile::ProjectileFramework *projectile,
                                 const Physics::IContactInfo &contact_info);

  private:
    Networking::ServerNetworkManager *m_server_network_manager;
    TickManager *m_tick_manager;
};
} // namespace Novaland::Character
