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

void CharacterHitHandler::HandleCharacterHit(Projectile::ProjectileFramework *hit_projectile,
                                             const Physics::IContactInfo &contact_info)
{
    m_character_message_tx->SendCharacterHitMessage(m_character, hit_projectile, contact_info);
    m_projectile_destroyer->QueueFree(hit_projectile->m_projectile.id);
}

} // namespace Novaland::Character
