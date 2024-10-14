////////////////////////////////////////////////////////////////////////////////
// File:        ProjectileInterpolation.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Math/Math.h"
#include "Math/Vec2.h"
#include "Projectile/Projectile.h"
#include "TimeUtils.h"

namespace Novaland::Projectile
{
struct ProjectileInterpolator : IComponent
{
  public:
    void Initialize()
    {
        delta_time_accumulator = 0.0f;
        auto transform = m_projectile->rigidbody->GetTransform();
        last_angle = transform.angle;
        target_angle = transform.angle;
        target_position = transform.position;
        last_position = transform.position;
        interpolated_transform = transform;
    }

  public:
    void Interpolate(f32 delta_time)
    {
        delta_time_accumulator += delta_time;

        if (delta_time_accumulator > tick_duration)
        {
            delta_time_accumulator = tick_duration;
        }

        f32 t = delta_time_accumulator / tick_duration;

        Vec2 position;
        f32 angle = 0.0f;

        if (lerp_count > 0)
        {
            f32 total_distance = 0.0f;

            // Assuming you have a buffer of distances already calculated: lerp_distances[]
            for (i32 i = 0; i < lerp_count - 1; i++)
            {
                total_distance += lerp_distances[i];
            }

            // Find which segment t falls into
            f32 distance_covered = t * total_distance;
            f32 accumulated_distance = 0.0f;
            size_t segment_index = 0;
            while (segment_index < lerp_count - 1 &&
                   accumulated_distance + lerp_distances[segment_index] < distance_covered)
            {
                accumulated_distance += lerp_distances[segment_index];
                ++segment_index;
            }

            // Compute local t for the segment
            f32 t_local = (distance_covered - accumulated_distance) / lerp_distances[segment_index];

            // Linear interpolation within the segment
            Vec2 start = lerp_positions[segment_index];
            Vec2 end = lerp_positions[segment_index + 1];
            position = start + (end - start) * t_local;
        }
        else
        {
            position = Vec2::Lerp(last_position, target_position, t);
            angle = Math::Lerp(last_angle, target_angle, t);
        }

        interpolated_transform.position = position;
        interpolated_transform.angle = angle;
    }

    void PreUpdate()
    {
        last_position = interpolated_transform.position;
        last_angle = interpolated_transform.angle;
        delta_time_accumulator = 0.0f;
    }

    void PostUpdate()
    {
        target_position = m_projectile->rigidbody->GetPosition();
        target_angle = m_projectile->rigidbody->GetAngle();
        lerp_count = 0;
    }

    void SetMidPoint(Vec2 point, f32 angle)
    {
        if (lerp_count >= 10)
        {
            return;
        }
        lerp_positions[lerp_count] = point;
        lerp_angles[lerp_count] = angle;

        if (lerp_count == 0)
        {
            lerp_distances[0] = point.Distance(last_position);
        }
        else
        {
            lerp_distances[lerp_count] = point.Distance(lerp_positions[lerp_count - 1]);
        }

        lerp_count++;
    }

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override
    {
        m_projectile = builder.Get<Projectile>();
        Initialize();
    }

  public:
    Physics::Transform interpolated_transform;

  private:
    Projectile *m_projectile = nullptr;

  private:
    bool is_midpoint_set = false;
    Vec2 midpoint;
    f32 mid_angle;
    const f32 tick_duration = TimeUtils::GetStepRate();
    f32 delta_time_accumulator;
    Vec2 last_position;
    Vec2 target_position;
    f32 last_angle;
    f32 target_angle;
    Vec2 lerp_positions[10];
    f32 lerp_angles[10];
    f32 lerp_distances[10];
    u32 lerp_count;
};
} // namespace Novaland::Projectile
