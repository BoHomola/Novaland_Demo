////////////////////////////////////////////////////////////////////////////////
// File:        CharacterHitController.cpp
// Author:      Bohumil Homola
// Date:        11/27/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterHitController.h"

namespace Novaland::Character
{

void CharacterHitHandler::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_character = builder.Get<Character>();
}

void CharacterHitHandler::HandleCharacterHit(const Ser::CharacterHit &message)
{
    if (OnCharacterHit)
    {
        OnCharacterHit({message.hitPosition.x, message.hitPosition.y}, message.hitAngle);
    }
    m_projectile_destroyer->QueueFree(message.projectileId);
}

} // namespace Novaland::Character
