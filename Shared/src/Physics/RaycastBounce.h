////////////////////////////////////////////////////////////////////////////////
// File:        RaycastBounce.h
// Author:      Bohumil Homola
// Date:        11/04/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Math/Vec2.h"
#include "Physics/CollisionHit.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/Rigidbody.h"
namespace Novaland::Physics
{

// struct RaycastBounceResult
// {
//     RaycastBounceResult()
//     {
//         points.reserve(15);
//     }
//     std::vector<CollisionHit> points;
//     std::vector<CollisionHit> left_points;
//     std::vector<CollisionHit> right_points;
//     Vec2 left;
//     Vec2 right;
//     Vec2 mid;
// };
//
// RaycastBounceResult RaycastBounce(PhysicsWorld *world, Vec2 start_point, Vec2 direction, f32 distance, f32 width);
} // namespace Novaland::Physics
