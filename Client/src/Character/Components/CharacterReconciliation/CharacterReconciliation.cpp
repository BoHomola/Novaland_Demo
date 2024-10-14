////////////////////////////////////////////////////////////////////////////////
// File:        CharacterReconciliation.cpp
// Author:      Bohumil Homola
// Date:        09/10/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterReconciliation.h"
#include "Logger.h"
#include "Math/Math.h"
#include "NovalandCommon.h"
#include "TimeUtils.h"

#ifndef RECONCILIATION_POSITION_THRESHOLD
#define RECONCILIATION_POSITION_THRESHOLD 0.1f
#endif

#ifndef RECONCILIATION_ANGLE_THRESHOLD
#define RECONCILIATION_ANGLE_THRESHOLD 0.1f
#endif

namespace Novaland::Character
{

void CharacterReconciliationComponent::RegisterDependencies(const ComponentDependencyBuilder &builder)
{
    character_snapshot_queue = builder.Get<CharacterSnapshotQueue>();
    character = builder.Get<Character>();
    character_definition = builder.Get<Definitions::CharacterDefinition>();
}

void CharacterReconciliationComponent::ReconcileCharacter(u32 updateTick, Physics::Transform &updateTransform,
                                                          Physics::Velocity &updateVelocity)
{
    PROFILE_SCOPE
    if (character_snapshot_queue->Empty())
    {
        return;
    }

    if (character_snapshot_queue->Front().tick > updateTick)
    {
        return;
    }

    while (character_snapshot_queue->Front().tick < updateTick)
    {
        character_snapshot_queue->Pop();
        if (character_snapshot_queue->Empty())
        {
            return;
        }
    }

    CharacterSnapshot character_snapshot = character_snapshot_queue->Front(); // copying the value
    character_snapshot_queue->Pop();
    assert(character_snapshot.tick == updateTick);

    f32 difference_magnitude = (updateTransform.position - character_snapshot.transform.position).Magnitude();
    f32 angle_difference = Math::Abs(updateTransform.angle - character_snapshot.transform.angle);

    if ((difference_magnitude > RECONCILIATION_POSITION_THRESHOLD ||
         angle_difference > RECONCILIATION_ANGLE_THRESHOLD) == false)
    {
        return;
    }

    assert(simulation_world->m_rigidbodies.size() == 0);

    Physics::Rigidbody *simulated_rigidbody =
        simulation_world->CreateCircleRigidbody(character_definition->rigidbody_properties, updateTransform, character,
                                                character_definition->collider_definition);

    simulated_rigidbody->SetVelocity(updateVelocity);
    simulated_rigidbody->SetTransform(updateTransform);

    for (int i = 0; i < character_snapshot_queue->Size(); i++)
    {
        CharacterSnapshot snapshot = character_snapshot_queue->Front();

        CharacterMoveComponent::Move(simulated_rigidbody, snapshot.state, snapshot.angular_speed, snapshot.move_speed,
                                     snapshot.input);
        simulation_world->UpdateWorld(TimeUtils::GetStepRate());

        // CharacterSnapshot new_snapshot = {
        //     snapshot.tick,
        //     simulated_rigidbody->GetTransform(),
        //     simulated_rigidbody->GetVelocity(),
        //     snapshot.input,
        // };
        snapshot.velocity = simulated_rigidbody->GetVelocity();
        snapshot.transform = simulated_rigidbody->GetTransform();
        character_snapshot_queue->Pop();
        character_snapshot_queue->Push(snapshot);
    }

    character->rigidbody->SetTransform(simulated_rigidbody->GetTransform());
    character->rigidbody->SetVelocity(simulated_rigidbody->GetVelocity());
    Logger::Info("Reconciled character");

    simulation_world->DestroyRigidbody(simulated_rigidbody);
}

} // namespace Novaland::Character
