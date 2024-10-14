////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDefinition.h
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include "Physics/ColliderDefinitions.h"
#include "Physics/Rigidbody.h"

namespace Novaland::Definitions
{

struct CharacterDefinition
{
    u32 definition_id;
    u32 base_health;
    u32 base_fire_delay;
    u32 base_fire_cooldown;
    u32 projectile_definition_id;
    u16 base_movement_speed;
    u16 base_angular_speed;
    Vec2 projectile_spawn_offet;
    Physics::CircleColliderDefinition collider_definition;
    Physics::RigidbodyParameters rigidbody_properties;
};

} // namespace Novaland::Definitions
