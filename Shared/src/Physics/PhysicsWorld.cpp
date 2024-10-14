////////////////////////////////////////////////////////////////////////////////
// File:        World.cpp
// Author:      Bohumil Homola
// Date:        06/25/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PhysicsWorld.h"
#include "Logger.h"
#include "Math/Math.h"
#include "NovalandCommon.h"
#include "Physics/Categories.h"
#include "Physics/RaycastResult.h"
#include "Rigidbody.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world.h"
#include <utility>

namespace Novaland::Physics
{

PhysicsWorld::PhysicsWorld()
{
    m_b2_world = new b2World(b2Vec2(0.0f, 0.0f));
    m_map = CreateMap();

    for (BoxColliderDefinition &map_object : m_map->box_colliders)
    {
        AddStaticBoxCollider(map_object);
    }

    collision_listener = new CollisionListener();
    m_b2_world->SetContactListener(collision_listener);
}

PhysicsWorld::~PhysicsWorld()
{
    delete m_b2_world;
    delete m_map;
    delete collision_listener;
}

void PhysicsWorld::AddStaticBoxCollider(const BoxColliderDefinition &def)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(def.x, def.y);
    bodyDef.angle = def.angle;
    b2PolygonShape shape;
    shape.SetAsBox(def.width, def.height);
    b2Body *body = m_b2_world->CreateBody(&bodyDef);
    b2Fixture *fixture = body->CreateFixture(&shape, 0.0f);
    b2Filter filter;
    filter.categoryBits = Categories::CATEGORY_STATIC;
    filter.maskBits = Categories::CATEGORY_ANY;
    filter.groupIndex = 0;
    fixture->SetFilterData(filter);
}

void PhysicsWorld::AddStaticCircleCollider(const CircleColliderDefinition &def)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(def.x, def.y);
    b2CircleShape shape;
    shape.m_radius = def.radius;
    b2Body *body = m_b2_world->CreateBody(&bodyDef);
    body->CreateFixture(&shape, 0.0f);
}

void PhysicsWorld::AddStaticPolygonCollider(const PolygonColliderDefinition &def)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(def.x, def.y);
    b2PolygonShape shape;
    shape.Set((b2Vec2 *)def.vertices.data(), def.vertices.size());
    b2Body *body = m_b2_world->CreateBody(&bodyDef);
    body->CreateFixture(&shape, 0.0f);
}

void PhysicsWorld::UpdateWorld(f32 delta_time)
{
    PROFILE_SCOPE
    for (Rigidbody *rigidbody : m_disposed_bodies)
    {
        m_b2_world->DestroyBody(rigidbody->b2body);
        delete rigidbody;
        rigidbody = nullptr;
    }

    m_disposed_bodies.clear();

    m_b2_world->Step(delta_time, 6, 2);
    UpdateRaycastRigidbodies();

    while (!m_transform_update_queue.empty())
    {
        auto pair = m_transform_update_queue.front();
        m_transform_update_queue.pop();

        Rigidbody *rigidbody = pair.first;
        rigidbody->SetTransform(pair.second);
    }
}

void PhysicsWorld::QueueTransformUpdate(Rigidbody *rb, const Transform &transform)
{
    m_transform_update_queue.push(std::make_pair(rb, transform));
}

Rigidbody *PhysicsWorld::AddRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                                      b2FixtureDef &fixture_definition, Entity::IEntity *entity,
                                      ColliderType colliderType)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(transform.position.x, transform.position.y);
    bodyDef.angle = transform.angle;
    bodyDef.linearDamping = rigidbody_parameters.linear_damping;
    bodyDef.angularDamping = rigidbody_parameters.angular_damping;

    b2Body *body = m_b2_world->CreateBody(&bodyDef);

    fixture_definition.density = rigidbody_parameters.density;
    fixture_definition.friction = rigidbody_parameters.friction;
    fixture_definition.restitution = rigidbody_parameters.restitution;
    fixture_definition.filter.groupIndex = rigidbody_parameters.group_index;
    fixture_definition.filter.maskBits = rigidbody_parameters.mask_bits;
    fixture_definition.filter.categoryBits = rigidbody_parameters.category_bits;

    Rigidbody *rigidbody = new Rigidbody();
    rigidbody->b2body = body;
    rigidbody->collider_type = colliderType;
    rigidbody->entity = entity;

    fixture_definition.userData.pointer = rigidbody;
    body->CreateFixture(&fixture_definition);
    m_rigidbodies.push_back(rigidbody);
    return rigidbody;
}

Rigidbody *PhysicsWorld::CreateCircleRigidbody(const RigidbodyParameters &rigidbody_parameters,
                                               const Transform &transform, Entity::IEntity *entity,
                                               const CircleColliderDefinition &circleCollider)
{
    b2FixtureDef fixdef;
    b2CircleShape circleShape;
    circleShape.m_radius = circleCollider.radius;
    fixdef.shape = &circleShape;
    return AddRigidbody(rigidbody_parameters, transform, fixdef, entity, ColliderType::Circle);
}

Rigidbody *PhysicsWorld::CreatePolygonRigidbody(const RigidbodyParameters &rigidbody_parameters,
                                                const Transform &transform, Entity::IEntity *entity,
                                                const PolygonColliderDefinition &polygonCollider)
{
    b2FixtureDef fixdef;
    b2PolygonShape polygonShape;

    b2Vec2 vertices[polygonCollider.vertices.size()];
    for (int i = 0; i < polygonCollider.vertices.size(); i++)
    {
        vertices[i].Set(polygonCollider.vertices[i].x, polygonCollider.vertices[i].y);
    }
    polygonShape.Set(vertices, polygonCollider.vertices.size());
    fixdef.shape = &polygonShape;

    return AddRigidbody(rigidbody_parameters, transform, fixdef, entity, ColliderType::Polygon);
}

Rigidbody *PhysicsWorld::CreateBoxRigidbody(const RigidbodyParameters &rigidbody_parameters, const Transform &transform,
                                            Entity::IEntity *entity, const BoxColliderDefinition &box_collider)
{
    b2FixtureDef fixdef;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(box_collider.width, box_collider.height);
    fixdef.shape = &polygonShape;

    return AddRigidbody(rigidbody_parameters, transform, fixdef, entity, ColliderType::Box);
}

Rigidbody *PhysicsWorld::CreateCircleRaycastRigidbody(const RigidbodyParameters &rigidbody_parameters,
                                                      const RaycastRigidbodyInitData &init_data,
                                                      Entity::IEntity *entity, const CircleColliderDefinition &collider)

{
    b2FixtureDef fixture_definition;
    b2CircleShape circleShape;
    circleShape.m_radius = collider.radius;
    fixture_definition.shape = &circleShape;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(init_data.from.x, init_data.from.y);
    bodyDef.angle = init_data.direction.ToAngle();

    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.0f;

    b2Body *body = m_b2_world->CreateBody(&bodyDef);

    fixture_definition.density = 0.0f;
    fixture_definition.friction = 0.0f;
    fixture_definition.restitution = 0.0f;
    fixture_definition.filter.groupIndex = 0;
    fixture_definition.filter.maskBits = rigidbody_parameters.mask_bits;
    fixture_definition.filter.categoryBits = 0;

    RaycastRigidbody *rigidbody = new RaycastRigidbody();
    rigidbody->b2body = body;
    rigidbody->collider_type = ColliderType::Circle;
    rigidbody->radius = collider.radius;
    rigidbody->entity = entity;

    rigidbody->from = init_data.from;
    rigidbody->direction = init_data.direction;
    rigidbody->speed = init_data.speed;
    rigidbody->SetAngle(rigidbody->direction.ToB2Angle()); // rotate 90 degrees to match b2box's angle

    fixture_definition.userData.pointer = rigidbody;
    body->CreateFixture(&fixture_definition);

    RaycastRadiusResult result =
        CircleCast(rigidbody->from, rigidbody->direction, rigidbody->radius, 100., Categories::CATEGORY_STATIC);
    if (result.hit)
    {
        rigidbody->hit_fixture = result.fixture;
        rigidbody->hit_normal = result.normal;
        rigidbody->has_hit = true;
        rigidbody->to = result.origin_point;
        rigidbody->hit_point = result.hit_point;
    }
    else
    {
        rigidbody->has_hit = false;
        rigidbody->to = rigidbody->to + rigidbody->direction * rigidbody->speed;
    }

    m_rigidbodies.push_back(rigidbody);
    m_raycast_rigidbodies.push_back(rigidbody);
    return rigidbody;
}

void PhysicsWorld::UpdateRaycastRigidbodies()
{
    PROFILE_SCOPE
    for (auto &rigidbody_ : m_raycast_rigidbodies)
    {
        auto rigidbody = static_cast<RaycastRigidbody *>(rigidbody_);
        auto whole_distance = rigidbody->from.Distance(rigidbody->to);
        auto traveled_distance = rigidbody->from.Distance(rigidbody->GetPosition());
        auto distance_left = whole_distance - traveled_distance;
        Vec2 oldPosition = rigidbody->GetPosition();

        if (distance_left >= rigidbody->speed)
        {
            Vec2 newPosition = oldPosition + (rigidbody->direction * rigidbody->speed);
            RaycastRadiusResult result = CircleCast(oldPosition, newPosition, rigidbody->radius,
                                                    rigidbody->b2body->GetFixtureList()->GetFilterData().maskBits);
            rigidbody->SetPosition(newPosition);
            if (result.hit)
            {
                collision_listener->RaycastBeginContact(rigidbody, result.fixture, result.hit_point, result.normal);
            }
        }
        else
        {
            Vec2 new_position;
            i32 max_iterations = 10;

            auto overflowing_distance = rigidbody->speed - distance_left;
            while (true)
            {
                max_iterations--;
                if (max_iterations == 0)
                {
                    Logger::Error("RaycastRigidbody::Update: max iterations reached");
                    break;
                }

                if (oldPosition.Distance(rigidbody->to) > 0.01f)
                {
                    auto first_half_result = CircleCast(oldPosition, rigidbody->to, rigidbody->radius,
                                                        rigidbody->b2body->GetFixtureList()->GetFilterData().maskBits);

                    if (first_half_result.hit)
                    {
                        collision_listener->RaycastBeginContact(rigidbody, first_half_result.fixture,
                                                                first_half_result.hit_point, first_half_result.normal);
                    }
                }

                if (rigidbody->has_hit)
                {

                    rigidbody->direction = rigidbody->direction.Reflect(rigidbody->hit_normal);
                    rigidbody->SetAngle(rigidbody->direction.ToB2Angle());
                    rigidbody->SetPosition(rigidbody->to);
                    collision_listener->RaycastBeginContact(rigidbody, rigidbody->hit_fixture, rigidbody->hit_point,
                                                            rigidbody->hit_normal);
                }

                RaycastRadiusResult result = CircleCast(rigidbody->to, rigidbody->direction, rigidbody->radius, 100.f,
                                                        Categories::CATEGORY_STATIC);
                rigidbody->from = rigidbody->to;

                if (result.hit)
                {
                    rigidbody->hit_fixture = result.fixture;
                    rigidbody->hit_normal = result.normal;
                    rigidbody->has_hit = true;
                    rigidbody->to = result.origin_point;
                    rigidbody->hit_point = result.hit_point;
                }
                else
                {
                    rigidbody->has_hit = false;
                    rigidbody->to = rigidbody->to + rigidbody->direction * overflowing_distance;
                }

                Vec2 second_half_position = rigidbody->from + rigidbody->direction * overflowing_distance;
                if (rigidbody->from.Distance(second_half_position) > 0.01f)
                {
                    auto second_half_result = CircleCast(rigidbody->from, second_half_position, rigidbody->radius,
                                                         rigidbody->b2body->GetFixtureList()->GetFilterData().maskBits);
                    if (second_half_result.hit)
                    {
                        collision_listener->RaycastBeginContact(rigidbody, second_half_result.fixture,
                                                                second_half_result.hit_point,
                                                                second_half_result.normal);
                    }
                }

                if (rigidbody->has_hit)
                {
                    auto hit_distance = rigidbody->from.Distance(rigidbody->to);
                    if (hit_distance < overflowing_distance)
                    {
                        // overflowing distance
                        overflowing_distance -= hit_distance;
                        continue;
                    }
                    else
                    {
                        new_position = rigidbody->from + rigidbody->direction * overflowing_distance;
                        break;
                    }
                }
                else
                {
                    new_position = rigidbody->to;
                    break;
                }
            }
            rigidbody->SetPosition(new_position);
        }
    }
}
RaycastRadiusResult PhysicsWorld::CircleCast(Vec2 start_point, Vec2 end, f32 radius, u16 mask_bits)
{
    PROFILE_SCOPE
    RaycastRadiusResult result;
    Vec2 dir = end - start_point;
    Vec2 perp_direction_left = dir.Perpendicular().Normalized();
    Vec2 perp_direction_right = perp_direction_left * -1.0f;
    Vec2 start_point_left = start_point + perp_direction_left * (radius);
    Vec2 start_point_right = start_point + perp_direction_right * (radius);

    Vec2 end_point_left = end + perp_direction_left * (radius);
    Vec2 end_point_right = end + perp_direction_right * (radius);

    RaycastHit raycast_result_left = RaycastClosest(start_point_left, end_point_left, mask_bits);
    RaycastHit raycast_result_right = RaycastClosest(start_point_right, end_point_right, mask_bits);

    // Determine which ray hit an object, if any.
    RaycastHit *selected_result = nullptr;
    bool isLeft = false;
    if (raycast_result_left.hit && raycast_result_right.hit)
    {
        selected_result = (raycast_result_left.fraction < raycast_result_right.fraction) ? &raycast_result_left
                                                                                         : &raycast_result_right;

        if (selected_result == &raycast_result_left)
        {
            isLeft = true;
        }
    }
    else if (raycast_result_left.hit)
    {
        selected_result = &raycast_result_left;
        isLeft = true;
    }
    else if (raycast_result_right.hit)
    {
        selected_result = &raycast_result_right;
    }
    else
    {
        result.hit = false;
        result.origin_point = end - dir.Normalized() * radius;
        return result;
    }

    Vec2 perp_direction = !isLeft ? perp_direction_left : perp_direction_right;
    Vec2 mid_point =
        selected_result->point + ((!isLeft ? perp_direction_left : perp_direction_right) * radius) -
        (-selected_result->normal.Normalized() * radius); // Move hit point back by radius along the normal.

    result.hit = true;
    result.origin_point = mid_point;
    result.hit_point = selected_result->point;
    result.normal = selected_result->normal;
    result.fixture = selected_result->fixture;

    return result;
}

RaycastRadiusResult PhysicsWorld::CircleCast(Vec2 start_point, Vec2 dir, f32 radius, f32 ray_length, u16 mask_bits)
{
    PROFILE_SCOPE
    Vec2 end_point = start_point + dir * ray_length;
    return CircleCast(start_point, end_point, radius, mask_bits);
}

bool PhysicsWorld::DestroyRigidbody(Rigidbody *rigidbody)
{
    if (rigidbody == nullptr)
    {
        Logger::Error("Body is null");
        return false;
    }

    m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), rigidbody), m_rigidbodies.end());
    m_raycast_rigidbodies.erase(std::remove(m_raycast_rigidbodies.begin(), m_raycast_rigidbodies.end(), rigidbody),
                                m_raycast_rigidbodies.end());

    m_disposed_bodies.push_back(rigidbody);
    return true;
}

std::vector<RaycastHit> PhysicsWorld::Raycast(const Vec2 &origin, const Vec2 &end, u16 mask_bits)
{
    PROFILE_SCOPE
    RaycastResult result;
    result.mask_bits = mask_bits;
    b2Vec2 b2origin = b2Vec2(origin.x, origin.y);
    b2Vec2 b2end = b2Vec2(end.x, end.y);
    m_b2_world->RayCast(&result, b2origin, b2end);
    return std::move(result.hits);
}

RaycastHit PhysicsWorld::RaycastClosest(const Vec2 &origin, const Vec2 &end, u16 mask_bits)
{
    PROFILE_SCOPE
    RaycastClosestResult result;
    result.mask_bits = mask_bits;
    b2Vec2 b2origin = b2Vec2(origin.x, origin.y);
    b2Vec2 b2end = b2Vec2(end.x, end.y);
    m_b2_world->RayCast(&result, b2origin, b2end);
    return std::move(result.hit_info);
}
} // namespace Novaland::Physics
