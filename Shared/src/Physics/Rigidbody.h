////////////////////////////////////////////////////////////////////////////////
// File:        Body.hpp
// Author:      Bohumil Homola
// Date:        06/25/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Entities/Entity.h"
#include "NovalandCommon.h"
#include "box2d/b2_body.h"
#include <Math/Vec2.h>

namespace Novaland::Physics
{

class PhysicsWorld;

struct RigidbodyParameters
{
    f32 linear_damping;
    f32 angular_damping;
    f32 density;
    f32 friction;
    f32 restitution;
    i16 group_index;
    u16 category_bits;
    u16 mask_bits;
};

enum class ColliderType
{
    Circle,
    Polygon,
    Box
};

struct Transform
{
    Vec2 position;
    f32 angle = 0;
};

struct Velocity
{
    Vec2 linear_velocity;
    f32 angular_velocity = 0;
};

struct Rigidbody
{
  public:
    Rigidbody();
    ~Rigidbody() = default;

    void ApplyForce(f32 move_speed, f32 angular_speed);
    Vec2 GetLinearVelocity() const;
    void SetVelocity(const Vec2 &velocity);
    void SetAngularVelocity(f32 angular_velocity);
    f32 GetAngularVelocity() const;
    void SetTransform(const Vec2 &position, f32 angle);
    void SetTransform(const Transform &transform);
    void SetVelocity(const Vec2 &velocity, f32 angular_velocity);
    void SetVelocity(const Velocity &velocity);
    const Transform GetTransform() const;
    const Velocity GetVelocity() const;
    Vec2 GetPosition() const;
    f32 GetAngle() const;
    void SetPosition(Vec2 position);
    void SetAngle(f32 angle);

  public:
    Entity::IEntity *entity;

  private:
    b2Body *b2body;
    ColliderType collider_type;
    friend class Novaland::Physics::PhysicsWorld;
};

} // namespace Novaland::Physics
