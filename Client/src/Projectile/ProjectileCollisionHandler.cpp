////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileCollisionHandeler.cpp
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "ProjectileCollisionHandler.h"
#include "DependencyInjector.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Projectile
{

ProjectileCollisionHandler::ProjectileCollisionHandler()
{
    m_projectile_container = Dependency::Get<Container<ProjectileFramework>>();
    m_world = Dependency::Get<Physics::PhysicsWorld>();

    m_world->collision_listener->AddOnCollisionEnterHandler(
        Entity::EntityType::ANY, Entity::EntityType::PROJECTILE,
        [this](Physics::Rigidbody *_, Physics::Rigidbody *projectile, const Physics::IContactInfo &contact_info) {
            HandleProjectileAnyEnterCollision(_, projectile, contact_info);
        });
}

ProjectileCollisionHandler::~ProjectileCollisionHandler()
{
}

void ProjectileCollisionHandler::HandleProjectileAnyEnterCollision(Physics::Rigidbody *_,
                                                                   Physics::Rigidbody *projectile_rb,
                                                                   const Physics::IContactInfo &contact_info)
{
    ProjectileFramework *projectile_framework = m_projectile_container->Get(projectile_rb->entity->id);
    if (projectile_framework == nullptr)
    {
        Logger::Error("ProjectileCollisionHandler::HandleProjectileAnyEnterCollision: projectile not found  ID: {}",
                      projectile_rb->entity->id);
        return;
    }
    projectile_framework->m_hit_controller.HandleProjectileAnyHit(contact_info);
}
} // namespace Novaland::Projectile
