////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCollisionHandeler.h
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterFramework.h"
#include "Physics/CollisionListener.h"
#include "Physics/Rigidbody.h"

namespace Novaland::Character
{
class CharacterCollisionHandler
{
  public:
    CharacterCollisionHandler();
    ~CharacterCollisionHandler();

  private:
    void HandleCharacterProjectileCollision(Physics::Rigidbody *character, Physics::Rigidbody *projectile,
                                            const Physics::IContactInfo &contact_info);

  private:
    Physics::PhysicsWorld *m_world = nullptr;
    Container<CharacterFramework> *m_character_container = nullptr;
    Container<Projectile::ProjectileFramework> *m_projectile_container = nullptr;
};

} // namespace Novaland::Character
