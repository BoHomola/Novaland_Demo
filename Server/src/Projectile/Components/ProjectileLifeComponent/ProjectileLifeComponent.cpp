////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileLifeComponent.cpp
// Author:      Bohumil Homola
// Date:        12/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileLifeComponent.h"

namespace Novaland::Projectile
{

void ProjectileLifeComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_projectile = builder.Get<Projectile>();
}

void ProjectileLifeComponent::Tick()
{
    if (m_projectile->destruction_tick <= m_tick_manager->GetCurrentTick())
    {

        m_projectile_destroyer->QueueFree(m_projectile->id);
    }
}
} // namespace Novaland::Projectile
