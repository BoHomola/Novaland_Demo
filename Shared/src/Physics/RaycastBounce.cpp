////////////////////////////////////////////////////////////////////////////////
// File:        RaycastBounce.cpp
// Author:      Bohumil Homola
// Date:        11/04/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "RaycastBounce.h"
#include "Math/Vec2.h"

namespace Novaland::Physics
{

// RaycastBounceResult RaycastBounce(PhysicsWorld *world, Vec2 start_point, Vec2 direction, f32 distance, f32 radius)
// {
//     PROFILE_SCOPE
//     RaycastBounceResult result;
//     f32 distance_left = distance;
//
//     // Normalize the direction to get a unit vector.
//     Vec2 normalized_direction = direction.Normalized();
//
//     // Calculate perpendicular vectors to the direction vector.
//     Vec2 perp_direction_left = normalized_direction.Perpendicular().Normalized();
//     Vec2 perp_direction_right = perp_direction_left * -1.0f;
//
//     // Calculate start points for the left and right rays.
//     Vec2 start_point_left = start_point + perp_direction_left * (radius);
//     Vec2 start_point_right = start_point + perp_direction_right * (radius);
//
//     result.left = start_point_left;
//     result.right = start_point_right;
//     result.mid = start_point;
//
//     result.points.push_back({start_point, -normalized_direction, 0.0f});
//     result.left_points.push_back({start_point_left, -normalized_direction});
//     result.right_points.push_back({start_point_right, -normalized_direction});
//
//     while (distance_left > 0)
//     {
//         // Calculate end points for the left and right rays.
//         Vec2 end_point_left = start_point_left + normalized_direction * distance_left;
//         Vec2 end_point_right = start_point_right + normalized_direction * distance_left;
//
//         // Perform raycasts for the left and right rays.
//         Physics::RaycastStaticResult raycast_result_left;
//         Physics::RaycastStaticResult raycast_result_right;
//
//         world->RaycastStatic(&raycast_result_left, start_point_left, end_point_left);
//         world->RaycastStatic(&raycast_result_right, start_point_right, end_point_right);
//
//         // Determine which ray hit an object, if any.
//         Physics::RaycastStaticResult *selected_result = nullptr;
//
//         bool isLeft = false;
//         if (raycast_result_left.hit && raycast_result_right.hit)
//         {
//             // If both rays hit, select the one with the closest hit.
//             selected_result = (raycast_result_left.closest_fraction < raycast_result_right.closest_fraction)
//                                   ? &raycast_result_left
//                                   : &raycast_result_right;
//             if (selected_result == &raycast_result_left)
//             {
//                 isLeft = true;
//             }
//
//             result.left_points.push_back({raycast_result_left.point, raycast_result_left.normal});
//             result.right_points.push_back({raycast_result_right.point, raycast_result_right.normal});
//         }
//         else if (raycast_result_left.hit)
//         {
//             selected_result = &raycast_result_left;
//             isLeft = true;
//
//             result.left_points.push_back({raycast_result_left.point, raycast_result_left.normal});
//         }
//         else if (raycast_result_right.hit)
//         {
//             selected_result = &raycast_result_right;
//             result.right_points.push_back({raycast_result_right.point, raycast_result_right.normal});
//         }
//
//         // If neither ray hit, add the end point and break.
//         if (!selected_result)
//         {
//             result.points.push_back({(end_point_left + end_point_right) * 0.5f, -normalized_direction, distance_left});
//             break;
//         }
//
//         // Process the hit.
//         CollisionHit hit;
//         hit.normal = selected_result->normal;
//
//         Vec2 perp_direction = !isLeft ? perp_direction_left : perp_direction_right;
//
//         Vec2 adjusted_hit = selected_result->point - (normalized_direction * (radius));
//
//         Vec2 mid_point = adjusted_hit + perp_direction * (radius);
//
//         hit.point = mid_point;
//         f32 raycast_distance = mid_point.Distance(start_point);
//         hit.distance = raycast_distance;
//         result.points.push_back(hit);
//
//         distance_left -= raycast_distance;
//
//         normalized_direction = normalized_direction.Reflect(selected_result->normal);
//
//         // Use the midpoint of the hit points of the left and right rays as the new start point.
//         start_point = mid_point;
//
//         perp_direction_left = normalized_direction.Perpendicular().Normalized();
//         perp_direction_right = perp_direction_left * -1.0f;
//         // Update start points for the left and right rays.
//         start_point_left = start_point + perp_direction_left * (radius);
//         start_point_right = start_point + perp_direction_right * (radius);
//
//         result.left_points.push_back({start_point_left, -normalized_direction});
//         result.right_points.push_back({start_point_right, -normalized_direction});
//     }
//
//     return std::move(result);
// }
} // namespace Novaland::Physics
