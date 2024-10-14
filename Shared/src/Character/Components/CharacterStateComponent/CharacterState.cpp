////////////////////////////////////////////////////////////////////////////////
// File:        CharacterState.cpp
// Author:      Bohumil Homola
// Date:        06/11/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterState.hpp"
#include "DependencyInjector.h"

namespace Novaland::Character
{

void CharacterStateComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
}

CharacterStateComponent::CharacterStateComponent()
{
    current_state = State::Active;
    tick_manager = Dependency::Get<TickManager>();
}

void CharacterStateComponent::AddState(StateData stateInfo)
{
    state_queue.push(stateInfo);
}

void CharacterStateComponent::AddState(uint32_t tickDuration, State state)
{
    StateData stateInfo{};
    stateInfo.startTick = tick_manager->GetCurrentTick();
    stateInfo.durationInTicks = tickDuration;
    stateInfo.state = state;
    AddState(stateInfo);
    UpdateState();
}

void CharacterStateComponent::UpdateState()
{
    while (!state_queue.empty())
    {
        StateData stateInfo = state_queue.top();
        if (stateInfo.GetEndTick() <= tick_manager->GetCurrentTick())
        {
            state_queue.pop();
        }
        else
        {
            current_state = stateInfo.state;
            break;
        }
    }

    if (state_queue.empty())
    {
        current_state = State::Active;
    }
}

bool CharacterStateComponent::IsImmobile() const
{
    return IsImmobile(current_state);
}

bool CharacterStateComponent::IsImmobile(State state)
{
    return state == State::Stunned || state == State::Snared || state == State::Dead || state == State::Casting;
}

bool CharacterStateComponent::IsCasting() const
{
    return IsCasting(current_state);
}

bool CharacterStateComponent::IsCasting(State state)
{
    return state == State::Casting;
}

bool CharacterStateComponent::CanCast() const
{
    return CanCast(current_state);
}

bool CharacterStateComponent::CanCast(State state)
{
    return state == State::Active;
}

bool CharacterStateComponent::IsDead() const
{
    return IsDead(current_state);
}

bool CharacterStateComponent::IsDead(State state)
{
    return state == State::Dead;
}

State CharacterStateComponent::GetState() const
{
    return current_state;
}

} // namespace Novaland::Character
