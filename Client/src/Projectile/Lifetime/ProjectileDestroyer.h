////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDestroyer.h
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Physics/PhysicsWorld.h"

namespace Novaland::Projectile
{

class ProjectileDestroyer
{
  public:
    ProjectileDestroyer();
    ~ProjectileDestroyer();

    void QueueFree(u32 projectile_id);
    void Clean();

  private:
    void DestroyProjectile(u32 projectile);

  public:
    std::function<void(u32 projectile_id)> OnProjectileDestroyed;

  private:
    Physics::PhysicsWorld *m_physics_world;
    std::queue<u32> m_free_queue;
};

} // namespace Novaland::Projectile
