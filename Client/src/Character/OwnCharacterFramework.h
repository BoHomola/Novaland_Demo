////////////////////////////////////////////////////////////////////////////////
// File:        OwnCharacterFramework.h
// Author:      Bohumil Homola
// Date:        11/26/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterFramework.h"
#include "Character/Components/CharacterFire/NetworkCharacterFireComponent.h"
#include "Character/Components/CharacterMoveComponent/CharacterMoveComponent.h"
#include "Character/Components/CharacterReconciliation/CharacterReconciliation.h"
#include "Components/CharacterInput/CharacterInputComponent.h"

namespace Novaland::Character
{
class OwnCharacterFramework : public CharacterFramework
{
  public:
    OwnCharacterFramework() : CharacterFramework()
    {
        is_own = true;
    }

    ~OwnCharacterFramework() override = default;

    void PostFixedUpdate() override;
    void FixedUpdate() override;

  public:
    CharacterInputComponent m_input_component{};
    CharacterMoveComponent m_move_component{};
    CharacterReconciliationComponent m_reconciliation_component{};
    CharacterSnapshotQueue m_character_snapshot_queue{};
    NetworkCharacterFireComponent m_network_character_fire_component{};
};
} // namespace Novaland::Character
