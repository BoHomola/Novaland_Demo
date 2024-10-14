////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInterpolation.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterInterpolation.h"

namespace Novaland::Character
{

void CharacterInterpolatorComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_character = builder.Get<Character>();
}

void CharacterInterpolatorComponent::Interpolate(f32 delta_time)
{
    delta_time_accumulator += delta_time;

    if (delta_time_accumulator > tick_duration)
    {
        delta_time_accumulator = tick_duration;
    }

    f32 t = delta_time_accumulator / tick_duration;
    Vec2 position = Vec2::Lerp(last_position, target_position, t);
    f32 angle = Math::Lerp(last_angle, target_angle, t);

    interpolated_transform.position = position;
    interpolated_transform.angle = angle;
}

void CharacterInterpolatorComponent::PreUpdate()
{
    last_position = interpolated_transform.position;
    last_angle = interpolated_transform.angle;
    delta_time_accumulator = 0.0f;
}

void CharacterInterpolatorComponent::PostUpdate()
{
    target_position = m_character->rigidbody->GetPosition();
    target_angle = m_character->rigidbody->GetAngle();
}

} // namespace Novaland::Character
