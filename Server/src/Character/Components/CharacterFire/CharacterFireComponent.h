////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFireComponent.h
// Author:      Bohumil Homola
// Date:        11/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Event/EventDispatcher.h"
#include "Base/Component/IComponent.h"
#include "Character/CharacterMessageTx.h"
#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "Definitions/CharacterDefinition.h"
#include "Physics/PhysicsWorld.h"
#include "Projectile/Lifetime/ProjectileCreator.h"

namespace Novaland::Character
{

class CharacterFireComponent : IComponent
{
  public:
    CharacterFireComponent()
    {
        m_character_message_tx = Dependency::Get<CharacterMessageTx>();
        m_physics_world = Dependency::Get<Physics::PhysicsWorld>();
        m_projectile_creator = Dependency::Get<Projectile::ProjectileCreator>();
    }
    ~CharacterFireComponent() override = default;

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    void HandleCharacterFire();

  private:
    CharacterStateComponent *m_character_state = nullptr;
    Character *m_character = nullptr;
    Definitions::CharacterDefinition *m_character_definition = nullptr;
    Event::EventDispatcher *m_event_dispatcher = nullptr;

  public:
    CharacterMessageTx *m_character_message_tx = nullptr;
    Physics::PhysicsWorld *m_physics_world = nullptr;
    Projectile::ProjectileCreator *m_projectile_creator = nullptr;
};
} // namespace Novaland::Character
