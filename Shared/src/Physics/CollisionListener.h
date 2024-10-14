////////////////////////////////////////////////////////////////////////////////
// File:        CollisionListener.hpp
// Author:      Bohumil Homola
// Date:        06/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Entities/Entity.h"
#include "Math/Math.h"
#include "Math/Vec2.h"
#include "NovalandCommon.h"
#include "Rigidbody.h"
#include "box2d/b2_contact.h"
#include "box2d/b2_world_callbacks.h"
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>

const u8 maximum_entity_type = 16;

namespace Novaland::Physics
{
u8 GetCollisionHash(u8 a, u8 b);

struct IContactInfo
{
    virtual Vec2 GetContactPoint() const = 0;
    virtual f32 GetHitAngle() const = 0;
};

struct b2ContactInfo : IContactInfo
{
    b2ContactInfo(const b2Contact *contact, const b2ContactImpulse *impulse) : contact(contact), impulse(impulse)
    {
    }
    const b2Contact *contact;
    const b2ContactImpulse *impulse;

    Vec2 GetContactPoint() const override
    {
        b2WorldManifold world_manifold{};
        contact->GetWorldManifold(&world_manifold);
        return Vec2(world_manifold.points[0].x, world_manifold.points[0].y);
    }

    f32 GetHitAngle() const override
    {
        b2WorldManifold world_manifold{};
        contact->GetWorldManifold(&world_manifold);
        f32 angle = Math::Atan2(world_manifold.normal.y, world_manifold.normal.x);
        return Math::Rad2Deg(angle);
    }
};

struct BasicContactInfo : IContactInfo
{
    Vec2 contact_point;
    f32 hit_angle;

    BasicContactInfo(Vec2 contact_point, f32 hit_angle) : contact_point(contact_point), hit_angle(hit_angle)
    {
    }

    Vec2 GetContactPoint() const override
    {
        return contact_point;
    }

    f32 GetHitAngle() const override
    {
        return hit_angle;
    }
};

class CollisionListener : public b2ContactListener
{
  public:
    CollisionListener() : on_collision_enter_callback_map(), on_collision_enter_post_solve_callback_map()
    {
        for (auto &callback : on_collision_enter_callback_map)
        {
            callback = nullptr;
        }
        for (auto &callback : on_collision_enter_post_solve_callback_map)
        {
            callback = nullptr;
        }
    }

    void AddOnCollisionEnterHandler(Entity::EntityType, Entity::EntityType,
                                    std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)>);

    void AddOnCollisionEnterPostSolveHandler(Entity::EntityType, Entity::EntityType,
                                             std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)>);

  private:
    void BeginContact(b2Contact *contact) override;
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;
    void RaycastBeginContact(Rigidbody *source_rigidbody, b2Fixture *hit_fixture, Vec2 hit_point,
                             Vec2 hit_normal);

  private:
    std::array<std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)>,
               maximum_entity_type * maximum_entity_type>
        on_collision_enter_callback_map;
    std::array<std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)>,
               maximum_entity_type * maximum_entity_type>
        on_collision_enter_post_solve_callback_map;

    friend class Novaland::Physics::PhysicsWorld;
};
} // namespace Novaland::Physics
