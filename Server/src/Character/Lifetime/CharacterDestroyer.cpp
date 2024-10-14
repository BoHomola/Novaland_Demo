////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDestroyer.cpp
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterDestroyer.h"

namespace Novaland::Character
{

void CharacterDestroyer::DestroyCharacter(u32 characterId)
{
    CharacterFramework *character_framework = character_container->Get(characterId);
    if (character_framework == nullptr)
    {
        return;
    }

    character_container->Remove(characterId);
    physics_world->DestroyRigidbody(character_framework->m_character.rigidbody);
    delete character_framework;
}

} // namespace Novaland::Character
