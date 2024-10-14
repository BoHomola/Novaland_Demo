#pragma once

#include "Entities/Entity.h"
#include "Physics/Rigidbody.h"
#include <box2d/b2_body.h>

namespace Novaland::Projectile
{

struct Projectile : public Entity::IEntity
{
    Projectile() : IEntity()
    {
        type = Entity::EntityType::PROJECTILE;
    }

    Physics::Rigidbody *rigidbody = nullptr;
    u32 owner_id = 0;
    u32 destruction_tick = 0;
};
} // namespace Novaland::Projectile
