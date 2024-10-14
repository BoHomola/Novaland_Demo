////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInputComponent.h
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Components/CharacterFire/CharacterFireComponent.h"
#include "Character/Components/CharacterInputComponent/CharacterInput.h"
#include "Character/Components/CharacterMoveComponent/CharacterMoveComponent.h"
#include "Character/SpecialAbility/ISpecialAbility.h"
#include "OverwriteBuffer.h"

namespace Novaland::Character
{

class CharacterInputComponent : IComponent
{
  public:
    CharacterInputComponent(){};

    ~CharacterInputComponent() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;
    void ProcessMovementInput(const Vec2 &movement_input, u32 tick);
    void ProcessInputKeys(u8 &keys, u32 tick);
    void ApplyInput();

  private:
    OverwriteBuffer<CharacterInput> movement_input_buffer{2};
    OverwriteBuffer<CharacterInput> keys_input_buffer{2};

  public:
    CharacterInput latest_input{};

  private:
    CharacterMoveComponent *m_move_component = nullptr;
    CharacterFireComponent *m_fire_component = nullptr;
    // ISpecialAbility *m_primary_special_ability = nullptr;
    ISpecialAbility *m_secondary_special_ability = nullptr;
};
} // namespace Novaland::Character
