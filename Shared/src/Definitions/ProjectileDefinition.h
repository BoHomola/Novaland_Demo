////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileDefinition.h
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

struct ProjectileDefinition
{
    u32 definition_id;
    u32 damage;
    f32 speed;
    u32 tick_duration;

    Physics::CircleColliderDefinition collider_definition;
    Physics::RigidbodyParameters rigidbody_properties;
};

} // namespace Novaland::Definitions
