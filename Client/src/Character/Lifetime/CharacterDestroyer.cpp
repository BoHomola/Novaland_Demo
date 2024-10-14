////////////////////////////////////////////////////////////////////////////////
// File:        CharacterDestroyer.cpp
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterDestroyer.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Character
{
void CharacterDestroyer::DestroyCharacter(u32 character_id)
{
    if (OnCharacterDestroyed)
    {
        OnCharacterDestroyed(character_id);
    }

    auto character_framework = character_container->Get(character_id);
    if (!character_framework)
    {
        return;
    }

    character_container->Remove(character_id);
    physics_world->DestroyRigidbody(character_framework->m_character.rigidbody);
    delete character_framework;
}
} // namespace Novaland::Character
