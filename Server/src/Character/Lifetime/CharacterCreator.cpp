///////////////////////////////////////////////////////////////////////////////
// File:        CharacterCreator.cpp
// Author:      Bohumil Homola
// Date:        09/03/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterCreator.h"
#include "Base/Component/ComponentDependencyBuilder.h"
#include "Character/CharacterFramework.h"
#include "Character/SpecialAbility/Flash/Flash.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Character
{

CharacterFramework *CharacterCreator::CreateCharacter(u32 definition_id)
{
    return CreateCharacter(definition_id, Physics::Transform());
}

CharacterFramework *CharacterCreator::CreateCharacter(u32 definition_id, const Physics::Transform &transform)
{
    CharacterFramework *character_framework = new CharacterFramework();
    character_framework->id = m_last_character_id++;

    Definitions::CharacterDefinition *definition =
        m_character_definition_provider->GetCharacterDefinition(definition_id);

    character_framework->definition = definition;
    character_framework->m_character.health = definition->base_health;
    character_framework->m_character.movement_speed = definition->base_movement_speed;
    character_framework->m_character.angular_speed = definition->base_angular_speed;
    character_framework->m_character.fire_delay = definition->base_fire_delay;
    character_framework->m_character.fire_cooldown = definition->base_fire_cooldown;
    character_framework->m_character.id = character_framework->id;

    character_framework->m_character.rigidbody =
        m_physics_world->CreateCircleRigidbody(definition->rigidbody_properties, transform,
                                               &character_framework->m_character, definition->collider_definition);

    // Defining special abilities. Do not forget to make an abstract factory
    Flash *flash = new Flash();
    // character_framework->m_primary_special_ability = flash;
    character_framework->m_secondary_special_ability = flash;

    character_framework->m_component_dependency_builder.Register(definition);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_character);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_input_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_move_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_state_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_hit_controller);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_fire_component);
    character_framework->m_component_dependency_builder.Register(&character_framework->m_event_dispatcher);
    character_framework->m_component_dependency_builder.Register(character_framework->m_secondary_special_ability);
    // character_framework->m_component_dependency_builder.Register(flash);

    ComponentDependencyBuilder &dependencyBuilder = character_framework->m_component_dependency_builder;
    character_framework->m_input_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_move_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_state_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_hit_controller.RegisterDependencies(dependencyBuilder);
    character_framework->m_fire_component.RegisterDependencies(dependencyBuilder);
    character_framework->m_event_dispatcher.RegisterDependencies(dependencyBuilder);
    character_framework->m_secondary_special_ability->RegisterDependencies(dependencyBuilder);

    m_character_container->Add(character_framework);

    return character_framework;
}
} // namespace Novaland::Character
