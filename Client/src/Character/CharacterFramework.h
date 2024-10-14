////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFramework.h
// Author:      Bohumil Homola
// Date:        11/25/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/ComponentDependencyBuilder.h"
#include "Character/Components/CharacterFire/CharacterFireComponent.h"
#include "Character/Components/CharacterHit/CharacterHitController.h"
#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "Components/CharacterInterpolation/CharacterInterpolation.h"
#include "Definitions/CharacterDefinition.h"

namespace Novaland::Character
{
class CharacterFramework : public ObjectWithId
{
  public:
    CharacterFramework() = default;

    virtual ~CharacterFramework() = default;

    virtual void Update(f32 delta_time);
    virtual void FixedUpdate();
    virtual void PostFixedUpdate();

  public:
    ComponentDependencyBuilder m_component_dependency_builder{};
    bool is_own = false;
    Definitions::CharacterDefinition *definition = nullptr;
    CharacterInterpolatorComponent m_interpolator{};
    Character m_character{};
    CharacterStateComponent m_state_component{};
    CharacterFireComponent m_fire_component{};
    CharacterHitHandler m_hit_controller{};
};
} //namespace Novaland::Character
