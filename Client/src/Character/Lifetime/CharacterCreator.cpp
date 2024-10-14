////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreator.cpp
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterCreator.h"
#include "Character/CharacterContainer.h"
#include "Character/CharacterFramework.h"

namespace Novaland::Character
{

CharacterFramework *CharacterCreator::CreateCharacter(u32 character_id, u32 definition_id, bool is_own)
{
    return CreateCharacter(character_id, definition_id, Physics::Transform(), is_own);
}

CharacterFramework *CharacterCreator::CreateCharacter(u32 character_id, u32 definition_id,
                                                      const Physics::Transform &transform, bool is_own)
{
    Definitions::CharacterDefinition *definition =
        m_character_definition_provider->GetCharacterDefinition(definition_id);
    CharacterFramework *character_framework = nullptr;
    if (is_own)
    {
        auto own_character_framework = new OwnCharacterFramework();
        character_framework = own_character_framework;
        m_character_container->own_character = own_character_framework;
    }
    else
    {
        character_framework = new CharacterFramework();
    }

    character_framework->id = character_id;
    character_framework->definition = definition;
    character_framework->m_character.health = definition->base_health;
    character_framework->m_character.movement_speed = definition->base_movement_speed;
    character_framework->m_character.angular_speed = definition->base_angular_speed;
    character_framework->m_character.fire_delay = definition->base_fire_delay;
    character_framework->m_character.fire_cooldown = definition->base_fire_cooldown;
    character_framework->m_character.rigidbody =
        m_physics_world->CreateCircleRigidbody(definition->rigidbody_properties, transform,
                                               &character_framework->m_character, definition->collider_definition);

    character_framework->m_component_dependency_builder.Register(character_framework->definition);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_interpolator);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_character);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_state_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_fire_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_hit_controller);

    ComponentDependencyBuilder &dependencyBuilder = character_framework->m_component_dependency_builder;
    character_framework->m_interpolator.RegisterDependencies(dependencyBuilder);
    character_framework->m_state_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_fire_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_hit_controller.RegisterDependencies(dependencyBuilder);

    if (is_own)
    {
        auto own_character_framework = static_cast<OwnCharacterFramework *>(character_framework);

        dependencyBuilder.Register(&own_character_framework->m_input_component);
        dependencyBuilder.Register(&own_character_framework->m_move_component);
        dependencyBuilder.Register(&own_character_framework->m_reconciliation_component);
        dependencyBuilder.Register(&own_character_framework->m_character_snapshot_queue);
        dependencyBuilder.Register(&own_character_framework->m_network_character_fire_component);

        own_character_framework->m_input_component.RegisterDependencies(dependencyBuilder);
        own_character_framework->m_move_component.RegisterDependencies(dependencyBuilder);
        own_character_framework->m_reconciliation_component.RegisterDependencies(dependencyBuilder);
        own_character_framework->m_character_snapshot_queue.RegisterDependencies(dependencyBuilder);
        own_character_framework->m_network_character_fire_component.RegisterDependencies(dependencyBuilder);
    }

    m_character_container->Add(character_framework);

    if (OnCharacterCreated)
    {
        OnCharacterCreated(character_framework, is_own);
    }

    return character_framework;
}

} // namespace Novaland::Character
