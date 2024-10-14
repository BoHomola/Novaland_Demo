////////////////////////////////////////////////////////////////////////////////
// File:        CharacterReconciliation.h
// Author:      Bohumil Homola
// Date:        09/10/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/IComponent.h"
#include "Character/Character.h"
#include "CharacterSnapshotQueue.h"
#include "Definitions/CharacterDefinition.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Character
{

class CharacterReconciliationComponent : IComponent
{
  public:
    CharacterReconciliationComponent()
    {
        simulation_world = new Physics::PhysicsWorld(); // find a way to copy real physics world in case map changes.
                                                        // but for now this works
    }

    void RegisterDependencies(const ComponentDependencyBuilder &builder) override;

    void ReconcileCharacter(u32 tick, Physics::Transform &transform, Physics::Velocity &velocity);

  private:
    Physics::PhysicsWorld *simulation_world;

  private:
    CharacterSnapshotQueue *character_snapshot_queue = nullptr;
    Character *character = nullptr;
    Definitions::CharacterDefinition *character_definition = nullptr;
};

} // namespace Novaland::Character
