////////////////////////////////////////////////////////////////////////////////
// File:        NLProjectileManager.cpp
// Author:      Bohumil Homola
// Date:        10/01/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "NLProjectileManager.h"
#include "Client.h"

NLProjectileManager::NLProjectileManager()
{
    engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint())
    {
        return;
    }
}

NLProjectileManager::~NLProjectileManager()
{
}

void NLProjectileManager::_bind_methods()
{
    GD_BIND_OBJECT(NLProjectileManager, projectile_scene, godot::PROPERTY_HINT_RESOURCE_TYPE, PackedScene)
    GD_BIND_OBJECT(NLProjectileManager, projectile_bounce_particle_scene, godot::PROPERTY_HINT_RESOURCE_TYPE,
                   PackedScene)
}

void NLProjectileManager::Init(Novaland::Client *client)
{
    this->client = client;

    client->projectile_creator->OnNewProjectileCreated = [this](Projectile::ProjectileFramework *projectile_framework) {
        OnProjectileCreated(projectile_framework);
    };

    client->projectile_destroyer->OnProjectileDestroyed = [this](u32 projectile_id) {
        OnProjectileDestroyed(projectile_id);
    };
}

void NLProjectileManager::OnUpdate()
{
    for (auto projectile : client->projectile_container->GetAll())
    {
        auto non_angle = projectile->m_projectile.rigidbody->GetTransform().angle;
        auto in_angle = projectile->m_interpolator.interpolated_transform.angle;
        auto position = projectile->m_interpolator.interpolated_transform.position;
        auto angle = projectile->m_interpolator.interpolated_transform.angle;
        Node3D *projectileNode = projectiles_dict[projectile->id];
        projectileNode->set_position({position.x, 0, position.y});
        projectileNode->set_rotation({0, -angle, 0});
    }
}

void NLProjectileManager::OnProjectileBounce(Projectile::ProjectileFramework *projectile,
                                             const Physics::IContactInfo &contact_info)
{
    if (projectile_bounce_particle_scene.is_valid())
    {
        godot::PackedScene *projectileBounceParticlePackedAsset = *projectile_bounce_particle_scene;
        Node *instance = projectileBounceParticlePackedAsset->instantiate();
        godot::Node3D *projectileBounceParticleNode = Object::cast_to<godot::Node3D>(instance);
        auto position = contact_info.GetContactPoint();
        f32 angle = contact_info.GetHitAngle();
        projectileBounceParticleNode->set_position({position.x, 0, position.y});
        projectileBounceParticleNode->set_rotation({0, -angle, 0});
        add_child(instance);
    }
}

void NLProjectileManager::OnProjectileCreated(Projectile::ProjectileFramework *projectile_framework)
{
    if (projectile_scene.is_valid())
    {
        godot::PackedScene *projectile_packed_asset = *projectile_scene;
        Node *instance = projectile_packed_asset->instantiate();
        godot::Node3D *projectile_node = Object::cast_to<godot::Node3D>(instance);
        auto position = projectile_framework->m_interpolator.interpolated_transform.position;
        auto angle = projectile_framework->m_interpolator.interpolated_transform.angle;
        projectile_node->set_position({position.x, 0, position.y});
        projectile_node->set_rotation({0, -angle, 0});
        projectile_node->set_name("Projectile_" + godot::String(std::to_string(projectile_framework->id).c_str()));
        add_child(instance);
        projectiles_dict[projectile_framework->id] = projectile_node;
        projectile_framework->m_hit_controller.OnProjectileCollision =
            [this, projectile_framework](const Physics::IContactInfo &contact_info) {
                OnProjectileBounce(projectile_framework, contact_info);
            };
    }
}

void NLProjectileManager::OnProjectileDestroyed(u32 projectile_id)
{
    if (projectiles_dict.contains(projectile_id))
    {
        auto projectileNode = projectiles_dict[projectile_id];
        projectiles_dict.erase(projectile_id);
        projectileNode->queue_free();
    }
}
