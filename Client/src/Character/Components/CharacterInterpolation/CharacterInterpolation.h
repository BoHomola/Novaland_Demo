////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInterpolation.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Character/Character.h"
#include "TimeUtils.h"

namespace Novaland::Character
{
struct CharacterInterpolatorComponent : IComponent
{
  public:
    CharacterInterpolatorComponent()
    {
        delta_time_accumulator = 0.0f;
        last_angle = 0.0f;
        target_angle = 0.0f;
        tick_duration = TimeUtils::GetStepRate();
    }

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

  public:
    void Interpolate(f32 delta_time);
    void PreUpdate();
    void PostUpdate();

  public:
    Physics::Transform interpolated_transform{};

  private:
    Character *m_character = nullptr;

  private:
    f32 tick_duration;
    f32 delta_time_accumulator;
    Vec2 last_position;
    Vec2 target_position;
    f32 last_angle;
    f32 target_angle;
};
} // namespace Novaland::Character
