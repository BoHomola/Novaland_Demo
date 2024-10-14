////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileFramework.h
// Author:      Bohumil Homola
// Date:        11/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/ObjectWithId.h"
#include "Definitions/ProjectileDefinition.h"
#include "Projectile/Components/ProjectileLifeComponent/ProjectileLifeComponent.h"
#include "Projectile/Projectile.h"
namespace Novaland::Projectile
{

class ProjectileFramework : public ObjectWithId
{
  public:
    ProjectileFramework() = default;
    ~ProjectileFramework() = default;

    void FixedUpdate();

  public:
    ComponentDependencyBuilder m_component_dependency_builder{};
    Definitions::ProjectileDefinition *m_definition = nullptr;
    Projectile m_projectile{};
    ProjectileLifeComponent m_projectile_life_component{};
};

} // namespace Novaland::Projectile
