////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDefinitionProvider.h
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "CharacterDefinition.h"
#include "NovalandCommon.h"
#include <unordered_map>
#include <vector>

namespace Novaland::Definitions
{

class CharacterDefinitionProvider
{
  public:
    CharacterDefinitionProvider();
    ~CharacterDefinitionProvider();

    void Initialize(const std::vector<CharacterDefinition> &character_definitions);
    CharacterDefinition *GetCharacterDefinition(u32 id);

  private:
    std::unordered_map<u32, CharacterDefinition *> m_character_definitions;
};

} // namespace Novaland::Definitions
