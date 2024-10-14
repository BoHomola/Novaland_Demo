#include "Projectile.h"

namespace Novaland::Projectile
{

    // Vec2 GetProjectilePosition(const Vec2 offset, const RigidbodyTransform &character_rigidbody_data)
    // {
    //
    //     Vec2 projectile_position;
    //     projectile_position.x = character_rigidbody_data.position.x + offset.x *
    //     std::cos(character_rigidbody_data.angle)
    //     -
    //                             offset.x * std::sin(character_rigidbody_data.angle);
    //
    //     projectile_position.y = character_rigidbody_data.position.y + offset.y *
    //     std::sin(character_rigidbody_data.angle)
    //     +
    //                             offset.y * std::cos(character_rigidbody_data.angle); return projectile_position;
    // }
    //
    // Projectile *CreateProjectile(Scene::Scene *scene, const RigidbodyTransform &character_rigidbody_data, u32
    // owner_id,
    //                              u32 definition_id)
    // {
    //
    //     // ProjectileDefinition *def = GetProjectileDefinition(scene->definitions, definition_id);
    //     //
    //     // Projectile *projectile = new Projectile();
    //     // projectile->owner_id = owner_id;
    //     // projectile->destruction_tick = scene->current_tick + TimeUtils::GetTicksFromSeconds(10);
    //     //
    //     // Vec2 offset = Vec2(1.0f, 1.0f);
    //     // Vec2 projectile_position = GetProjectilePosition(offset, character_rigidbody_data);
    //     //
    //     // RigidbodyData projectile_rigidbody_data;
    //     //
    //     // projectile_rigidbody_data.position = projectile_position;
    //     // projectile_rigidbody_data.angle = character_rigidbody_data.angle;
    //     // projectile_rigidbody_data.properties = def->properties;
    //     // projectile_rigidbody_data.user_data = projectile;
    //     // projectile_rigidbody_data.type = Entity::EntityType::Projectile;
    //     //
    //     // projectile->definition = def;
    //     // projectile->rigidbody =
    //     //     scene->AddProjectile(&projectile->entity_metadata, projectile_rigidbody_data, def, projectile);
    //     //
    //     // PushProjectile(projectile->rigidbody, def->speed);
    //     // return projectile;
    // }
    // void DestroyProjectile(Scene::Scene *scene, Projectile *projectile)
    // {
    //     scene->RemoveRigidbody(projectile->rigidbody, projectile->entity_metadata.entityId);
    //     delete projectile;
    //     projectile = nullptr;
    // }
    //
    // void UpdateProjectile(Projectile *projectile, Scene::Scene *scene)
    // {
    //     // if (projectile->destruction_tick <= scene->current_tick)
    //     // {
    //     //     DestroyProjectile(scene, projectile);
    //     // }
    // }
    //
    // void Projectile::Push()
    // {
    // b2Vec2 force = rigidbody->b2body->GetWorldVector({0, 1});
    // force *= speed * rigidbody->b2body->GetMass();
    // rigidbody->b2body->ApplyForceToCenter(force, true);
    // }

} // namespace Novaland::Projectile
