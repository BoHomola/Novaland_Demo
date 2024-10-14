////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreator.h
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/CharacterFramework.h"
#include "Definitions/CharacterDefinitionProvider.h"

namespace Novaland::Character
{

class CharacterCreator
{
  public:
    CharacterCreator()
    {
        Dependency::Register<CharacterCreator>(this);
        m_character_definition_provider = Dependency::Get<Definitions::CharacterDefinitionProvider>();
        m_character_container = Dependency::Get<Container<CharacterFramework>>();
        m_physics_world = Dependency::Get<Physics::PhysicsWorld>();
        m_last_character_id = 0;
    }
    ~CharacterCreator() = default;

    CharacterFramework *CreateCharacter(u32 definition_id);
    CharacterFramework *CreateCharacter(u32 definition_id, const Physics::Transform &transform);

  private:
    u32 m_last_character_id = 0;
    Definitions::CharacterDefinitionProvider *m_character_definition_provider;
    Physics::PhysicsWorld *m_physics_world;
    Container<CharacterFramework> *m_character_container;
};
} // namespace Novaland::Character
