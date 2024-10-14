////////////////////////////////////////////////////////////////////////////////
// File:        CharacterSnapshotQueue.h
// Author:      Bohumil Homola
// Date:        09/10/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Character/Character.h"
#include "Character/Components/CharacterInput/CharacterInputComponent.h"
#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "NovalandCommon.h"
#include "Physics/Rigidbody.h"
#include "Tick/TickManger.h"
#include <queue>

namespace Novaland::Character
{
struct CharacterSnapshot
{
    u32 tick = 0;
    Physics::Transform transform;
    Physics::Velocity velocity;
    Vec2 input;
    f32 angular_speed = 0;
    f32 move_speed = 0;
    State state = State::Active;
};

class CharacterSnapshotQueue : IComponent
{
  public:
    CharacterSnapshotQueue()
    {
        tick_manager = Dependency::Get<TickManager>();
    }

    ~CharacterSnapshotQueue() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override
    {
        character = builder.Get<Character>();
        character_state = builder.Get<CharacterStateComponent>();
        character_input = builder.Get<CharacterInputComponent>();
    }

    void CaptureCharacterSnapshot()
    {
        Physics::Velocity velocity = character->rigidbody->GetVelocity();
        Vec2 input = character_input->latest_input.movement_input;
        Physics::Transform transform = character->rigidbody->GetTransform();
        State state = character_state->GetState();

        CharacterSnapshot snapshot = {
            tick_manager->GetCurrentTick(), transform, velocity, input, character->angular_speed,
            character->movement_speed,      state,
        };

        character_snapshots.push(snapshot);
    }

    void Push(CharacterSnapshot &snapshot)
    {
        character_snapshots.push(snapshot);
    }

    void Pop()
    {
        character_snapshots.pop();
    }

    CharacterSnapshot &Front()
    {
        return character_snapshots.front();
    }

    bool Empty()
    {
        return character_snapshots.empty();
    }

    u32 Size()
    {
        return character_snapshots.size();
    }

  private:
    std::queue<CharacterSnapshot> character_snapshots = {};
    TickManager *tick_manager = nullptr;

  private:
    CharacterInputComponent *character_input = nullptr;
    Character *character = nullptr;
    CharacterStateComponent *character_state = nullptr;
};

} // namespace Novaland::Character
