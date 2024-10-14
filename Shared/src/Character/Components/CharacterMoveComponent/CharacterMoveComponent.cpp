////////////////////////////////////////////////////////////////////////////////
// File:        CharacterController.cpp
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterMoveComponent.h"
#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "NovalandCommon.h"
#include "Physics/Rigidbody.h"

namespace Novaland::Character
{
void CharacterMoveComponent::Move(Vec2 input)
{
    Move(character->rigidbody, character_state->GetState(), character->angular_speed,
                                  character->movement_speed, input);
}

void CharacterMoveComponent::Move(Physics::Rigidbody *rigidbody, const State &state, f32 angular_speed, f32 move_speed,
                                  const Vec2 &input)
{
    if (CharacterStateComponent::IsImmobile(state))
    {
        return;
    }

    angular_speed = input.x * angular_speed;
    move_speed = input.y * move_speed;
    rigidbody->ApplyForce(move_speed, angular_speed);
}

void CharacterMoveComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    character = builder.Get<Character>();
    character_state = builder.Get<CharacterStateComponent>();
}

} // namespace Novaland::Character
