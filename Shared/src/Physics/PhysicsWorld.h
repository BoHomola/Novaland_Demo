////////////////////////////////////////////////////////////////////////////////
// File:        World.hpp
// Author:      Bohumil Homola
// Date:        06/24/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "CollisionListener.h"
#include "Entities/Entity.h"
#include "Map.h"
#include "Physics/Categories.h"
#include "Physics/RaycastResult.h"
#include "Physics/RaycastRigidbody.h"
#include "Rigidbody.h"
#include <vector>

namespace Novaland::Physics
{

struct PhysicsWorld
{
  public:
    PhysicsWorld();
    ~PhysicsWorld();
    void UpdateWorld(f32 deltaTime);
    Rigidbody *CreateCircleRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                                     Entity::IEntity *entity, const CircleColliderDefinition &collider);

    Rigidbody *CreatePolygonRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                                      Entity::IEntity *entity, const PolygonColliderDefinition &collider);

    Rigidbody *CreateBoxRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                                  Entity::IEntity *entity, const BoxColliderDefinition &collider);

    Rigidbody *CreateCircleRaycastRigidbody(const RigidbodyParameters &rigidbody_parameters,
                                            const RaycastRigidbodyInitData &init_data, Entity::IEntity *entity,
                                            const CircleColliderDefinition &collider);

    bool DestroyRigidbody(Rigidbody *rigidbody);
    void QueueTransformUpdate(Rigidbody *, const Transform &transform);
    std::vector<RaycastHit> Raycast(const Vec2 &origin, const Vec2 &direction,
                                    u16 mask_bits = Categories::CATEGORY_ANY);
    RaycastHit RaycastClosest(const Vec2 &origin, const Vec2 &end, u16 mask_bits = Categories::CATEGORY_ANY);
    std::vector<RaycastHit> RaycastDirection(const Vec2 &origin, const Vec2 &dir, f32 ray_length = 100.f,
                                             u16 mask_bits = Categories::CATEGORY_ANY);
    RaycastHit RaycastDirectionClosest(const Vec2 &origin, const Vec2 &dir, f32 ray_length = 100.f,
                                       u16 mask_bits = Categories::CATEGORY_ANY);

  private:
    void AddStaticPolygonCollider(const PolygonColliderDefinition &def);
    void AddStaticCircleCollider(const CircleColliderDefinition &def);
    void AddStaticBoxCollider(const BoxColliderDefinition &def);
    void UpdateRaycastRigidbodies();
    RaycastRadiusResult CircleCast(Vec2 start_point, Vec2 dir, f32 radius, f32 ray_length,
                                      u16 mask_bits = Categories::CATEGORY_STATIC);
    RaycastRadiusResult CircleCast(Vec2 start_point, Vec2 end, f32 radius,
                                      u16 mask_bits = Categories::CATEGORY_STATIC);

    Rigidbody *AddRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                            b2FixtureDef &fixture_definition, Entity::IEntity *entity, ColliderType colliderType);

  public:
    Map *m_map;
    std::vector<Rigidbody *> m_rigidbodies;
    CollisionListener *collision_listener;

  private:
    b2World *m_b2_world;
    std::vector<Rigidbody *> m_raycast_rigidbodies;
    std::vector<Rigidbody *> m_disposed_bodies;
    std::queue<std::pair<Rigidbody *, Transform>> m_transform_update_queue;

    friend PhysicsWorld *CreateWorld();
    friend void DestroyWorld(PhysicsWorld *world);
};
} // namespace Novaland::Physics
