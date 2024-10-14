////////////////////////////////////////////////////////////////////////////////
// File:        CharacterMoveComponent.h
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Character/Character.h"
#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "Physics/Rigidbody.h"

namespace Novaland::Character
{
class CharacterMoveComponent : IComponent
{
  public:
    CharacterMoveComponent() = default;
    ~CharacterMoveComponent() override = default;
    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;
    void Move(Vec2 input);
    static void Move(Physics::Rigidbody *rigidbody, const State &state, f32 angular_speed, f32 move_speed, const Vec2& input);

  public:
    Character *character = nullptr;
    CharacterStateComponent *character_state = nullptr;
};
} // namespace Novaland::Character
