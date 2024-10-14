////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInputComponent.cpp
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterInputComponent.h"
#include "Input/Input.h"

namespace Novaland::Character
{

void CharacterInputComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_move_component = builder.Get<CharacterMoveComponent>();
    m_fire_component = builder.Get<CharacterFireComponent>();
}

void CharacterInputComponent::ProcessInput(CharacterInput &input)
{
    latest_input = input;
    m_message_tx->SendCharacterInput(latest_input);
}

void CharacterInputComponent::ApplyInput()
{
    m_move_component->Move(latest_input.movement_input);

    if (latest_input.keys & Input::InputKey::ATTACK)
    {
        m_fire_component->HandleCharacterFireStart();
    }

    // if (keys & Input::InputKey::SPECIAL_ABILITY_1)
    // {
    //     m_primary_special_ability->Proceed();
    // }

    // if (latest_input.keys & Input::InputKey::SPECIAL_ABILITY_2)
    // {
    //     m_secondary_special_ability->Proceed();
    // }
}
} // namespace Novaland::Character
