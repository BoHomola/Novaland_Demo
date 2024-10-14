////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCreator.h
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Definitions/ProjectileDefinitionProvider.h"
#include "NovalandCommon.h"
#include "Physics/Rigidbody.h"
#include "Projectile/ProjectileFramework.h"
#include "Tick/TickManger.h"

namespace Novaland::Projectile
{

class ProjectileCreator
{
  public:
    ProjectileCreator();
    ~ProjectileCreator();

    ProjectileFramework *CreateProjectile(u32 definition_id, u32 owned_id, const Physics::Transform &transform);

  private:
    Definitions::ProjectileDefinitionProvider *m_projectile_definition_provider;
    Container<ProjectileFramework> *m_projectile_container;
    TickManager *m_tick_manager;
    Physics::PhysicsWorld *m_physics_world;
    u32 m_last_projectile_id;
};

} // namespace Novaland::Projectile
