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
#include "Physics/Rigidbody.h"
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
}
ProjectileCreator::~ProjectileCreator()
{
}

ProjectileFramework *ProjectileCreator::CreateProjectile(const ProjectileInitilizationData &data)
{
    ProjectileFramework *projectile_framework = new ProjectileFramework();

    auto definition = m_projectile_definition_provider->GetProjectileDefinition(data.projectile_definition_id);

    if (definition == nullptr)
    {
        Logger::Error("ProjectileCreator::CreateProjectile: Projectile definition not found");
        delete projectile_framework;
        return nullptr;
    }

    projectile_framework->id = data.projectile_id;
    projectile_framework->m_definition = definition;
    projectile_framework->m_projectile.id = data.projectile_id;
    projectile_framework->m_projectile.owner_id = data.owner_character_id;
    projectile_framework->m_projectile.destruction_tick = m_tick_manager->GetCurrentTick() + definition->tick_duration;

    Physics::Transform transform;
    transform.position = data.transform.position;
    transform.angle = data.transform.angle;

    Physics::RaycastRigidbodyInitData rigidbody_init_data;
    rigidbody_init_data.speed = definition->speed;
    rigidbody_init_data.direction = Vec2::FromRadian(transform.angle);
    rigidbody_init_data.from = transform.position;

    projectile_framework->m_projectile.rigidbody = m_physics_world->CreateCircleRaycastRigidbody(
        definition->rigidbody_properties, rigidbody_init_data, &projectile_framework->m_projectile,
        definition->collider_definition);

    ComponentDependencyBuilder &builder = projectile_framework->m_component_dependency_builder;

    builder.Register(&projectile_framework->m_projectile);
    builder.Register(projectile_framework->m_definition);
    builder.Register(&projectile_framework->m_hit_controller);
    builder.Register(&projectile_framework->m_life_component);
    builder.Register(&projectile_framework->m_interpolator);

    projectile_framework->m_life_component.RegisterDependencies(builder);
    projectile_framework->m_hit_controller.RegisterDependencies(builder);
    projectile_framework->m_interpolator.RegisterDependencies(builder);

    if (OnNewProjectileCreated)
    {
        OnNewProjectileCreated(projectile_framework);
    }

    m_projectile_container->Add(projectile_framework);

    return projectile_framework;
}
} // namespace Novaland::Projectile
