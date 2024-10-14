////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCollisionHandeler.h
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Physics/CollisionListener.h"
#include "Physics/Rigidbody.h"
#include "Projectile/ProjectileFramework.h"

namespace Novaland::Projectile
{

class ProjectileCollisionHandler
{
  public:
    ProjectileCollisionHandler();
    ~ProjectileCollisionHandler();

  private:
    void HandleProjectileAnyEnterCollision(Physics::Rigidbody *_, Physics::Rigidbody *projectile,
                                           const Physics::IContactInfo &contact_info);

  private:
    Physics::PhysicsWorld *m_world;
    Container<ProjectileFramework> *m_projectile_container;
};

} // namespace Novaland::Projectile
