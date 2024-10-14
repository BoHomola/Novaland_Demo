////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDestroyer.cpp
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileDestroyer.h"
#include "Base/Component/Container.h"
#include "DependencyInjector.h"
#include "Projectile/ProjectileFramework.h"

namespace Novaland::Projectile
{


void ProjectileDestroyer::DestroyProjectile(u32 projectileId)
{
    Container<ProjectileFramework> *projectile_container = Dependency::Get<Container<ProjectileFramework>>();
    ProjectileFramework *projectile = projectile_container->Get(projectileId);
    if (projectile == nullptr)
    {
        return;
    }

    projectile_container->Remove(projectileId);
    m_physics_world->DestroyRigidbody(projectile->m_projectile.rigidbody);
    delete projectile;
}

void ProjectileDestroyer::Clean()
{
    while (!m_free_queue.empty())
    {
        DestroyProjectile(m_free_queue.front());
        m_free_queue.pop();
    }
}

void ProjectileDestroyer::QueueFree(u32 projectileId)
{
    m_free_queue.push(projectileId);
}

} // namespace Novaland::Projectile
