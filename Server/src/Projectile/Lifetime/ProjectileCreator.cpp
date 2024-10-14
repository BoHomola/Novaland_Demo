////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCreator.cpp
// Author:      Bohumil Homola
// Date:        09/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileCreator.h"
#include "Definitions/ProjectileDefinitionProvider.h"
#include "DependencyInjector.h"
#include "Physics/PhysicsWorld.h"
#include "Projectile/ProjectileFramework.h"
#include "Tick/TickManger.h"

namespace Novaland::Projectile
{

ProjectileCreator::ProjectileCreator()
{
    Dependency::Register<ProjectileCreator>(this);
    m_projectile_definition_provider = Dependency::Get<Definitions::ProjectileDefinitionProvider>();
    m_projectile_container = Dependency::Get<Container<ProjectileFramework>>();
    m_tick_manager = Dependency::Get<TickManager>();
    m_physics_world = Dependency::Get<Physics::PhysicsWorld>();
    m_last_projectile_id = 0;

    this->m_last_projectile_id = 0;
}
ProjectileCreator::~ProjectileCreator()
{
}

ProjectileFramework *ProjectileCreator::CreateProjectile(u32 definition_id, u32 owned_id,
                                                         const Physics::Transform &transform)
{
    ProjectileFramework *projectile_framework = new ProjectileFramework();
    projectile_framework->id = m_last_projectile_id++;
    projectile_framework->m_projectile.id = projectile_framework->id;

    auto definition = m_projectile_definition_provider->GetProjectileDefinition(definition_id);

    if (definition == nullptr)
    {
        Logger::Error("ProjectileCreator::CreateProjectile: Projectile definition not found");
        delete projectile_framework;
        return nullptr;
    }

    projectile_framework->m_definition = definition;

    projectile_framework->m_projectile.owner_id = owned_id;
    projectile_framework->m_projectile.destruction_tick = m_tick_manager->GetCurrentTick() + definition->tick_duration;

    Physics::RaycastRigidbodyInitData rigidbody_init_data;
    rigidbody_init_data.speed = definition->speed;
    rigidbody_init_data.direction = Vec2::FromRadian(transform.angle + Math::Deg2Rad(90));
    rigidbody_init_data.from = transform.position;

    projectile_framework->m_projectile.rigidbody = m_physics_world->CreateCircleRaycastRigidbody(
        definition->rigidbody_properties, rigidbody_init_data, &projectile_framework->m_projectile,
        definition->collider_definition);

    projectile_framework->m_component_dependency_builder.Register(projectile_framework->m_definition);
    projectile_framework->m_component_dependency_builder.Register(&projectile_framework->m_projectile);
    projectile_framework->m_component_dependency_builder.Register(&projectile_framework->m_projectile_life_component);

    projectile_framework->m_projectile_life_component.RegisterDependencies(
        projectile_framework->m_component_dependency_builder);

    m_projectile_container->Add(projectile_framework);

    return projectile_framework;
}
} // namespace Novaland::Projectile
