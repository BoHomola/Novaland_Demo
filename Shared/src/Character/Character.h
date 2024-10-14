#pragma once

#include "Entities/Entity.h"
#include "NovalandCommon.h"
#include "Physics/Rigidbody.h"

namespace Novaland::Character
{

struct Character : public Entity::IEntity
{
    Character() : IEntity()
    {
        type = Entity::EntityType::CHARACTER;
    }

    Physics::Rigidbody *rigidbody = nullptr;
    u32 health = 0;
    f32 movement_speed = 0;
    f32 angular_speed = 0;
    u32 fire_delay = 0;
    u32 fire_cooldown = 0;
};

} // namespace Novaland::Character
