////////////////////////////////////////////////////////////////////////////////
// File:        Flash.h
// Author:      Bohumil Homola
// Date:        12/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Character.h"
#include "Character/Components/CharacterInputComponent/CharacterInputComponent.h"
#include "Character/SpecialAbility/ISpecialAbility.h"

namespace Novaland::Character
{
class Flash : public ISpecialAbility
{
  public:
    ~Flash() override = default;
    void Proceed() override;
    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

  private:
    Character *m_character = nullptr;
    CharacterInputComponent *m_input_component = nullptr;
    CharacterStateComponent *m_state = nullptr;
};
} // namespace Novaland::Character
