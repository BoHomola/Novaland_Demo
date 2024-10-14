////////////////////////////////////////////////////////////////////////////////
// File:        CharacterState.hpp
// Author:      Bohumil Homola
// Date:        06/11/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "NovalandCommon.h"
#include "Tick/TickManger.h"
#include <queue>

namespace Novaland::Character
{
enum class State : u8
{
    Active = 0,
    Casting = 10,
    Snared = 20,
    Stunned = 30,
    Dead = 40,
};

struct StateData
{
    u32 startTick;
    u32 durationInTicks;
    State state;

    bool operator<(const StateData &other) const
    {
        return state < other.state;
    }

    u32 GetEndTick() const
    {
        return startTick + durationInTicks;
    }
};

class CharacterStateComponent : IComponent
{
  private:
    std::priority_queue<StateData> state_queue;
    State current_state;
    TickManager *tick_manager = nullptr;

  public:
    CharacterStateComponent();

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    void AddState(StateData stateInfo);
    void AddState(uint32_t tickDuration, State state);
    void UpdateState();
    bool IsImmobile() const;
    static bool IsImmobile(State state);
    bool IsCasting() const;
    static bool IsCasting(State state);
    bool CanCast() const;
    static bool CanCast(State state);
    bool IsDead() const;
    static bool IsDead(State state);
    State GetState() const;
};
} // namespace Novaland::Character
