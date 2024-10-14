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

struct ProjectileInitilizationData
{
    u32 projectile_id = 0;
    u32 projectile_definition_id = 0;
    u32 owner_character_id = 0;
    Physics::Transform transform;
    // Physics::Velocity velocity;
    // f32 direction;
    // Vec2 start_position;
};

class ProjectileCreator
{
  public:
    ProjectileCreator();
    ~ProjectileCreator();

    ProjectileFramework *CreateProjectile(const ProjectileInitilizationData &data);

  public:
    std::function<void(ProjectileFramework *)> OnNewProjectileCreated = nullptr;

  private:
    Definitions::ProjectileDefinitionProvider *m_projectile_definition_provider;
    Container<ProjectileFramework> *m_projectile_container;
    TickManager *m_tick_manager;
    Physics::PhysicsWorld *m_physics_world;
};

} // namespace Novaland::Projectile
