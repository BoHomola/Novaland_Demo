////////////////////////////////////////////////////////////////////////////////
// File:        CharacterInputComponent.h
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "Base/Component/IComponent.h"
#include "Character/CharacterMessageTx.h"
#include "Character/Components/CharacterFire/CharacterFireComponent.h"
#include "Character/Components/CharacterInputComponent/CharacterInput.h"
#include "Character/Components/CharacterMoveComponent/CharacterMoveComponent.h"
#include "DependencyInjector.h"

namespace Novaland::Character
{

class CharacterInputComponent : IComponent
{
  public:
    CharacterInputComponent()
    {
        m_message_tx = Dependency::Get<CharacterMessageTx>();
    };

    ~CharacterInputComponent() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    void ProcessInput(CharacterInput &input);
    void ApplyInput();

  public:
    CharacterInput latest_input;

  public:
    CharacterMoveComponent *m_move_component = nullptr;
    CharacterFireComponent *m_fire_component = nullptr;

  public:
    CharacterMessageTx *m_message_tx = nullptr;
};
} // namespace Novaland::Character
