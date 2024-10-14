////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileController.cpp
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileController.h"
#include "DependencyInjector.h"
#include "Tick/TickManger.h"

namespace Novaland::Projectile
{

ProjectileController::ProjectileController()
{
    Dependency::Register<ProjectileController>(this);
    m_tick_manager = Dependency::Get<TickManager>();
}

ProjectileController::~ProjectileController()
{
}

void ProjectileController::UpdateProjectile(Projectile *projectile)
{
    if (m_tick_manager->GetCurrentTick() >= projectile->destruction_tick)
    {
        DestroyProjectile(projectile);
    }
}

} // namespace Novaland::Projectile
