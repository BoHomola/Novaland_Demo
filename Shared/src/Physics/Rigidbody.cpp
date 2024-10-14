////////////////////////////////////////////////////////////////////////////////
// File:        Body.cpp
// Author:      Bohumil Homola
// Date:        06/25/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Rigidbody.h"

namespace Novaland::Physics
{

Rigidbody::Rigidbody()
{
}

void Rigidbody::ApplyForce(f32 move_speed, f32 angular_speed)
{
    f32 torque = b2body->GetInertia() * angular_speed;
    b2body->ApplyTorque(-torque, true);

    b2Vec2 forward(0, 1);
    b2Vec2 force = b2body->GetWorldVector(forward);
    force.x *= move_speed * b2body->GetMass();
    force.y *= move_speed * b2body->GetMass();
    b2body->ApplyForceToCenter(force, true);
}

void Rigidbody::SetVelocity(const Vec2 &velocity)
{
    b2body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void Rigidbody::SetAngularVelocity(f32 angular_velocity)
{
    b2body->SetAngularVelocity(angular_velocity);
}

void Rigidbody::SetVelocity(const Vec2 &velocity, f32 angular_velocity)
{
    b2body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    b2body->SetAngularVelocity(angular_velocity);
}

void Rigidbody::SetVelocity(const Velocity &velocity)
{
    b2body->SetLinearVelocity(b2Vec2(velocity.linear_velocity.x, velocity.linear_velocity.y));
    b2body->SetAngularVelocity(velocity.angular_velocity);
}

Vec2 Rigidbody::GetLinearVelocity() const
{
    return Vec2(b2body->GetLinearVelocity().x, b2body->GetLinearVelocity().y);
}

f32 Rigidbody::GetAngularVelocity() const
{
    return b2body->GetAngularVelocity();
}

void Rigidbody::SetTransform(const Vec2 &position, f32 angle)
{
    b2body->SetTransform(b2Vec2(position.x, position.y), angle);
}

void Rigidbody::SetTransform(const Transform &transform)
{
    b2body->SetTransform(b2Vec2(transform.position.x, transform.position.y), transform.angle);
}

const Transform Rigidbody::GetTransform() const
{
    Transform data;
    data.position.x = b2body->GetPosition().x;
    data.position.y = b2body->GetPosition().y;
    data.angle = b2body->GetAngle();
    return data;
}

const Velocity Rigidbody::GetVelocity() const
{
    Velocity data;
    data.linear_velocity.x = b2body->GetLinearVelocity().x;
    data.linear_velocity.y = b2body->GetLinearVelocity().y;
    data.angular_velocity = b2body->GetAngularVelocity();
    return data;
}

Vec2 Rigidbody::GetPosition() const
{
    return Vec2(b2body->GetPosition().x, b2body->GetPosition().y);
}

f32 Rigidbody::GetAngle() const
{
    return b2body->GetAngle();
}

void Rigidbody::SetPosition(Vec2 position)
{
    b2body->SetTransform(b2Vec2(position.x, position.y), b2body->GetAngle());
}

void Rigidbody::SetAngle(f32 angle)
{
    b2body->SetTransform(b2body->GetPosition(), angle);
}

} // namespace Novaland::Physics
