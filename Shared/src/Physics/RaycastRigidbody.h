////////////////////////////////////////////////////////////////////////////////
// File:        RaycastRigidbody.h
// Author:      Bohumil Homola
// Date:        11/12/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Physics/Rigidbody.h"

namespace Novaland::Physics
{
struct RaycastRigidbodyInitData
{
    f32 speed;
    Vec2 direction;
    Vec2 from;
};

struct RaycastRigidbody : public Rigidbody
{
  private:
    f32 speed;
    Vec2 direction;
    Vec2 from;
    Vec2 to;
    f32 radius;
    bool has_hit;
    Vec2 hit_normal;
    Vec2 hit_point;
    b2Fixture *hit_fixture;
    friend class Novaland::Physics::PhysicsWorld;
};

} // namespace Novaland::Physics
