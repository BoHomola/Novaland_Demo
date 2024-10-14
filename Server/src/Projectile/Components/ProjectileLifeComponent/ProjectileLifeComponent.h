////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileLifeComponent.h
// Author:      Bohumil Homola
// Date:        12/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Projectile/Lifetime/ProjectileDestroyer.h"
#include "Projectile/Projectile.h"
#include "Tick/TickManger.h"
namespace Novaland::Projectile
{

class ProjectileLifeComponent : IComponent
{
  public:
    ProjectileLifeComponent()
    {
        m_projectile_destroyer = Dependency::Get<ProjectileDestroyer>();
        m_tick_manager = Dependency::Get<TickManager>();
    }
    ~ProjectileLifeComponent() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    void Tick();

  private:
    ProjectileDestroyer *m_projectile_destroyer = nullptr;
    TickManager *m_tick_manager = nullptr;

  public:
    Projectile *m_projectile = nullptr;
};
} // namespace Novaland::Projectile
