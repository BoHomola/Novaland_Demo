////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDefinitionsProvider.cpp
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterDefinitionProvider.h"
#include "DependencyInjector.h"

namespace Novaland::Definitions
{

    CharacterDefinitionProvider::CharacterDefinitionProvider()
    {
        Dependency::Register<CharacterDefinitionProvider>(this);
    }

    CharacterDefinitionProvider::~CharacterDefinitionProvider()
    {
        Dependency::Unregister<CharacterDefinitionProvider>();
        for (auto it = m_character_definitions.begin(); it != m_character_definitions.end(); it++)
        {
            delete it->second;
        }
    }

    void CharacterDefinitionProvider::Initialize(const std::vector<CharacterDefinition> &character_definitions)
    {
        for (auto &character_definition : character_definitions)
        {
            m_character_definitions[character_definition.definition_id] = new CharacterDefinition(character_definition);
        }
    }

    CharacterDefinition *CharacterDefinitionProvider::GetCharacterDefinition(u32 id)
    {
        auto it = m_character_definitions.find(id);
        if (it != m_character_definitions.end())
        {
            return it->second;
        }

        return nullptr;
    }

} // namespace Novaland::Definitions
