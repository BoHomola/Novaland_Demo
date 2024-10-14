////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDestroyer.h
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "DependencyInjector.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Projectile
{

class ProjectileDestroyer
{
  public:
    ProjectileDestroyer()
    {
        Dependency::Register<ProjectileDestroyer>(this);
        m_physics_world = Dependency::Get<Physics::PhysicsWorld>();
    }

    ~ProjectileDestroyer() = default;

    void QueueFree(u32 projectile);
    void Clean();

  private:
    void DestroyProjectile(u32 projectile);

  private:
    Physics::PhysicsWorld *m_physics_world;
    std::queue<u32> m_free_queue;
};

} // namespace Novaland::Projectile
