////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFireComponent.cpp
// Author:      Bohumil Homola
// Date:        11/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterFireComponent.h"

namespace Novaland::Character
{

void CharacterFireComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_character_state = builder.Get<CharacterStateComponent>();
    m_character_definition = builder.Get<Definitions::CharacterDefinition>();
}

void CharacterFireComponent::HandleCharacterFireStart()
{
    if (!m_character_state->CanCast())
    {
        return;
    }
    m_character_state->AddState(m_character_definition->base_fire_cooldown, State::Casting);
}

void CharacterFireComponent::HandleCharacterFireFinish(const Ser::CharacterFire &message)
{
    Projectile::ProjectileInitilizationData projectile_initilization_data;

    projectile_initilization_data.transform.position = {message.projectileState.position.x,
                                                        message.projectileState.position.y};
    projectile_initilization_data.transform.angle = message.projectileState.rotation;
    projectile_initilization_data.projectile_definition_id = message.definitionId;
    projectile_initilization_data.owner_character_id = message.characterId;
    projectile_initilization_data.projectile_id = message.projectileState.entityId;

    m_projectile_creator->CreateProjectile(projectile_initilization_data);
}

} // namespace Novaland::Character
