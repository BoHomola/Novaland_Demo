////////////////////////////////////////////////////////////////////////////////
// File:        ClientCharacter.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Character/CharacterFramework.h"
#include "Export.h"
#include "Physics/Rigidbody.h"

EXPORT Novaland::Physics::Rigidbody *GetCharacterRigidbody(Novaland::Character::CharacterFramework *character)
{
    return character->m_character.rigidbody;
}

EXPORT Novaland::Physics::Transform GetCharacterInterpolatedTransform(
    Novaland::Character::CharacterFramework *character)
{
    return character->m_interpolator.interpolated_transform;
}

EXPORT u32 GetCharacterId(Novaland::Character::CharacterFramework *character)
{
    return character->id;
}
