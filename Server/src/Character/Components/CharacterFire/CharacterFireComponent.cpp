////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFireComponent.h
// Author:      Bohumil Homola
// Date:        11/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterFireComponent.h"
namespace Novaland::Character
{

void CharacterFireComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    m_character_state = builder.Get<CharacterStateComponent>();
    m_character = builder.Get<Character>();
    m_character_definition = builder.Get<Definitions::CharacterDefinition>();
    m_event_dispatcher = builder.Get<Event::EventDispatcher>();
}

void CharacterFireComponent::HandleCharacterFire()
{
    PROFILE_SCOPE
    if (!m_character_state->CanCast())
    {
        return;
    }

    m_character_state->AddState(m_character_definition->base_fire_cooldown, State::Casting);

    m_character_message_tx->SendCharacterStartFireMessage(m_character->id);
    m_event_dispatcher->QueueEvent(m_character_definition->base_fire_delay, [this]() {
        Physics::Transform character_transform = m_character->rigidbody->GetTransform();

        Physics::Transform projectile_transform;
        // Compute rotated x-offset
        projectile_transform.position.x =
            character_transform.position.x +
            m_character_definition->projectile_spawn_offet.x * std::cos(character_transform.angle) -
            m_character_definition->projectile_spawn_offet.y * std::sin(character_transform.angle);

        // Compute rotated y-offset
        projectile_transform.position.y =
            character_transform.position.y +
            m_character_definition->projectile_spawn_offet.x * std::sin(character_transform.angle) +
            m_character_definition->projectile_spawn_offet.y * std::cos(character_transform.angle);

        projectile_transform.angle = character_transform.angle;

        // check for object inbetween the offset
        auto raycast_result = m_physics_world->RaycastClosest(
            character_transform.position, projectile_transform.position, Categories::CATEGORY_STATIC);
        if (raycast_result.hit)
        {
            projectile_transform.position = raycast_result.point;
            Logger::Info("Raycast hit");
        }

        float radians = projectile_transform.angle + Math::Deg2Rad(90);
        Vec2 normalized_direction(Math::Cos(radians), Math::Sin(radians));

        auto projectile = m_projectile_creator->CreateProjectile(m_character_definition->projectile_definition_id,
                                                                 m_character->id, projectile_transform);

        m_character_message_tx->SendCharacterFinishFireMessage(m_character, projectile, projectile_transform.position,
                                                               normalized_direction.ToAngle());
    });
}

} // namespace Novaland::Character
