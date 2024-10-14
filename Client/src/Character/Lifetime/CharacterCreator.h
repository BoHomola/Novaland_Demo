////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreator.h
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterContainer.h"
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
        m_character_container = Dependency::Get<CharacterContainer>();
        m_physics_world = Dependency::Get<Physics::PhysicsWorld>();
    }

    ~CharacterCreator()
    {
        Dependency::Unregister<CharacterCreator>();
    }

    CharacterFramework *CreateCharacter(u32 definition_id, u32 character_id, bool is_own);
    CharacterFramework *CreateCharacter(u32 definition_id, u32 character_id, const Physics::Transform &transform,
                                        bool is_own);

    void CreateCharacter();

  public:
    std::function<void(CharacterFramework *, bool)> OnCharacterCreated = nullptr;

  private:
    Definitions::CharacterDefinitionProvider *m_character_definition_provider;
    Physics::PhysicsWorld *m_physics_world;
    CharacterContainer *m_character_container;
};

} // namespace Novaland::Character
