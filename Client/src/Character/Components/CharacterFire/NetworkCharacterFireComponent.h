////////////////////////////////////////////////////////////////////////////////
// File:        CharacterFireComponent.h
// Author:      Bohumil Homola
// Date:        11/28/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Character/Components/CharacterStateComponent/CharacterState.hpp"
#include "Definitions/CharacterDefinition.h"
#include "DependencyInjector.h"
#include "Projectile/Lifetime/ProjectileCreator.h"
#include "SerServer.h"
namespace Novaland::Character
{

class NetworkCharacterFireComponent : IComponent
{
  public:
    NetworkCharacterFireComponent()
    {
        m_projectile_creator = Dependency::Get<Projectile::ProjectileCreator>();
    }

    void RegisterDependencies(const ComponentDependencyBuilder &) override;

  public:
    void HandleCharacterFireStart();
    void HandleCharacterFireFinish(const Ser::CharacterFire &);

  private:
    CharacterStateComponent *m_state = nullptr;
    Definitions::CharacterDefinition *m_character_definition = nullptr;

  public:
    Projectile::ProjectileCreator *m_projectile_creator;
};

} // namespace Novaland::Character
