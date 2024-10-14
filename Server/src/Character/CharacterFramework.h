////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFramework.h
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/ComponentDependencyBuilder.h"
#include "Base/Component/Event/EventDispatcher.h"
#include "Base/Component/ObjectWithId.h"
#include "Character/Components/CharacterFire/CharacterFireComponent.h"
#include "Character/Components/CharacterHit/CharacterHitController.h"
#include "Character/Components/CharacterInputComponent/CharacterInputComponent.h"
#include "Character/SpecialAbility/ISpecialAbility.h"
#include "Definitions/CharacterDefinition.h"

namespace Novaland::Character
{
class CharacterFramework : public ObjectWithId
{
  public:
    CharacterFramework() = default;

    ~CharacterFramework() = default;

    void FixedUpdate();

  public:
    ComponentDependencyBuilder m_component_dependency_builder;
    Definitions::CharacterDefinition *definition = nullptr;
    CharacterInputComponent m_input_component{};
    CharacterMoveComponent m_move_component{};
    Character m_character{};
    CharacterStateComponent m_state_component{};
    CharacterHitHandler m_hit_controller{};
    CharacterFireComponent m_fire_component{};
    Event::EventDispatcher m_event_dispatcher{};
    // Create Special Ability component that handles both primary and secondary
    // ISpecialAbility *m_primary_special_ability = nullptr;
    ISpecialAbility *m_secondary_special_ability = nullptr;
};
} // namespace Novaland::Character
