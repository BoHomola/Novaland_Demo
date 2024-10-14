////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInpucComponent.cpp
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
    // m_primary_special_ability = builder.Get<ISpecialAbility>();
    m_secondary_special_ability = builder.Get<ISpecialAbility>();
}

void CharacterInputComponent::ProcessMovementInput(const Vec2 &movement_input, u32 tick)
{
    CharacterInput input;
    input.movement_input = movement_input;
    input.tick = tick;
    input.keys = 0;
    movement_input_buffer.Push(input);
}

void CharacterInputComponent::ProcessInputKeys(u8 &keys, u32 tick)
{
    CharacterInput input;
    input.tick = tick;
    input.keys = keys;
    keys_input_buffer.Push(input);
}

void CharacterInputComponent::ApplyInput()
{
    if (movement_input_buffer.Empty())
    {
        // empty buffer
        return;
    }

    // TOOD: Synchronize movement and keys by tick. Probably use priority queue for the buffer and a way to assure the keys are
    // always exeuted. This is naive solution that works locally or on stable interent
    latest_input = movement_input_buffer.Pop();
    latest_input.keys = keys_input_buffer.Pop().keys;

    m_move_component->Move(latest_input.movement_input);
    if (latest_input.keys & Input::InputKey::ATTACK)
    {
        m_fire_component->HandleCharacterFire();
    }

    if (latest_input.keys & Input::InputKey::SPECIAL_ABILITY_2)
    {
        m_secondary_special_ability->Proceed();
    }
}

} // namespace Novaland::Character
