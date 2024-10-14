////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileFramework.h
// Author:      Bohumil Homola
// Date:        11/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/ComponentDependencyBuilder.h"
#include "Base/Component/ObjectWithId.h"
#include "Definitions/ProjectileDefinition.h"
#include "Projectile/Components/ProjectileHitComponent/ProjectileHitComponent.h"
#include "Projectile/Components/ProjectileInterpolation/ProjectileInterpolation.h"
#include "Projectile/Components/ProjectileLifeComponent/ProjectileLifeComponent.h"
#include "Projectile/Projectile.h"

namespace Novaland::Projectile
{

class ProjectileFramework : public ObjectWithId
{
  public:
    ProjectileFramework() = default;
    virtual ~ProjectileFramework() = default;

    virtual void FixedUpdate();
    virtual void PostFixedUpdate();
    virtual void Update(f32 delta_time);

    ComponentDependencyBuilder m_component_dependency_builder{};
    Definitions::ProjectileDefinition *m_definition = nullptr;
    Projectile m_projectile{};
    ProjectileHitController m_hit_controller{};
    ProjectileLifeComponent m_life_component{};
    ProjectileInterpolator m_interpolator{};
};

} // namespace Novaland::Projectile
