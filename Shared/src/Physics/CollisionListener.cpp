////////////////////////////////////////////////////////////////////////////////
// File:        CollisionListener.cpp
// Author:      Bohumil Homola
// Date:        06/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CollisionListener.h"
#include "Entities/Entity.h"
#include "Logger.h"
#include "NovalandCommon.h"
#include "Rigidbody.h"
#include <string>
#include <utility>

namespace Novaland::Physics
{

// hash for up to 256 combinations of 16 entities
u8 GetCollisionHash(u8 a, u8 b)
{
    assert(a < maximum_entity_type && b < maximum_entity_type);

    if (a > b)
    {
        std::swap(a, b);
    }
    return (a << 4) | b;
}

void CollisionListener::AddOnCollisionEnterHandler(
    Entity::EntityType entity_type_a, Entity::EntityType entity_type_b,
    std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)> callback)
{
#ifdef DEBUG_BUILD
    if (entity_type_a > entity_type_b)
    {
        Logger::Error("parameter must be in ascending order {}, {}", std::to_string(entity_type_a),
                      std::to_string(entity_type_b));
        return;
    }
#endif
    u16 hash = GetCollisionHash(entity_type_a, entity_type_b);
    if (on_collision_enter_callback_map[hash] != nullptr)
    {
        Logger::Warn("Collision callback for {} and {} already exists", std::to_string(entity_type_a),
                     std::to_string(entity_type_b));
    }

    on_collision_enter_callback_map[hash] = callback;
}

void CollisionListener::AddOnCollisionEnterPostSolveHandler(
    Entity::EntityType entity_type_a, Entity::EntityType entity_type_b,
    std::function<void(Rigidbody *, Rigidbody *, const IContactInfo &)> callback)
{
#ifdef DEBUG_BUILD
    if (entity_type_a > entity_type_b)
    {
        Logger::Error("parameter must be in ascending order {}, {}", std::to_string(entity_type_a),
                      std::to_string(entity_type_b));
        return;
    }
#endif
    u16 hash = GetCollisionHash(entity_type_a, entity_type_b);
    if (on_collision_enter_post_solve_callback_map[hash] != nullptr)
    {
        Logger::Warn("Collision callback for {} and {} already exists", std::to_string(entity_type_a),
                     std::to_string(entity_type_b));
    }

    on_collision_enter_post_solve_callback_map[hash] = callback;
}

void CollisionListener::BeginContact(b2Contact *contact)
{
    Rigidbody *rigidbodyA = static_cast<Rigidbody *>(contact->GetFixtureA()->GetUserData().pointer);
    Rigidbody *rigidbodyB = static_cast<Rigidbody *>(contact->GetFixtureB()->GetUserData().pointer);

    b2ContactInfo info{contact, nullptr};
    Entity::EntityType typeA = Entity::EntityType::NONE;
    if (rigidbodyA != nullptr)
    {
        typeA = rigidbodyA->entity->type;
        auto callback = on_collision_enter_callback_map[GetCollisionHash(typeA, Entity::EntityType::ANY)];
        if (callback != nullptr)
        {
            callback(rigidbodyB, rigidbodyA, info);
        }
    }

    Entity::EntityType typeB = Entity::EntityType::NONE;
    if (rigidbodyB != nullptr)
    {
        typeB = rigidbodyB->entity->type;
        auto callback = on_collision_enter_callback_map[GetCollisionHash(typeB, Entity::EntityType::ANY)];
        if (callback != nullptr)
        {
            callback(rigidbodyA, rigidbodyB, info);
        }
    }

    u16 hash = GetCollisionHash(typeA, typeB);

    auto callback = on_collision_enter_callback_map[hash];
    if (callback != nullptr)
    {
        if (typeA > typeB)
        {
            std::swap(rigidbodyA, rigidbodyB);
        }
        callback(rigidbodyA, rigidbodyB, info);
    }
}

void CollisionListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    Rigidbody *rigidbodyA = static_cast<Rigidbody *>(contact->GetFixtureA()->GetUserData().pointer);
    Rigidbody *rigidbodyB = static_cast<Rigidbody *>(contact->GetFixtureB()->GetUserData().pointer);

    b2ContactInfo info{contact, impulse};

    Entity::EntityType typeA = Entity::EntityType::NONE;
    if (rigidbodyA != nullptr)
    {
        typeA = rigidbodyA->entity->type;
        auto callbackAny = on_collision_enter_post_solve_callback_map[GetCollisionHash(typeA, Entity::EntityType::ANY)];
        if (callbackAny != nullptr)
        {
            callbackAny(rigidbodyB, rigidbodyA, info);
        }
    }

    Entity::EntityType typeB = Entity::EntityType::NONE;
    if (rigidbodyB != nullptr)
    {
        typeB = rigidbodyB->entity->type;
        auto callbackAny = on_collision_enter_post_solve_callback_map[GetCollisionHash(typeB, Entity::EntityType::ANY)];
        if (callbackAny != nullptr)
        {
            callbackAny(rigidbodyA, rigidbodyB, info);
        }
    }

    u16 hash = GetCollisionHash(typeA, typeB);

    auto callback = on_collision_enter_post_solve_callback_map[hash];
    if (callback != nullptr)
    {
        if (typeA > typeB)
        {
            std::swap(rigidbodyA, rigidbodyB);
        }
        b2ContactInfo info{contact, impulse};
        callback(rigidbodyA, rigidbodyB, info);
    }
}

void CollisionListener::RaycastBeginContact(Rigidbody *source_rigidbody, b2Fixture *hit_fixture, Vec2 hit_point,
                                            Vec2 hit_normal)
{

    Rigidbody *hit_rb = reinterpret_cast<Rigidbody *>(hit_fixture->GetUserData().pointer);

    f32 hit_angle = hit_normal.ToAngle();
    BasicContactInfo info{hit_point, hit_angle};

    auto source_type = source_rigidbody->entity->type;
    auto callbackAny = on_collision_enter_callback_map[GetCollisionHash(source_type, Entity::EntityType::ANY)];
    if (callbackAny != nullptr)
    {
        callbackAny(hit_rb, source_rigidbody, info);
    }

    auto hit_type = hit_rb == nullptr ? Entity::EntityType::NONE : hit_rb->entity->type;

    u16 hash = GetCollisionHash(source_type, hit_type);
    auto callback = on_collision_enter_callback_map[hash];
    if (callback != nullptr)
    {
        if (source_type > hit_type)
        {
            std::swap(source_rigidbody, hit_rb);
        }
        callback(source_rigidbody, hit_rb, info);
    }
}
} // namespace Novaland::Physics
