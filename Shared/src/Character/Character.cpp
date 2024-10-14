#include "Character.h"
#include <Logger.h>
#include <string>

namespace Novaland::Character
{

    // bool CharacterFire(Character *character, Scene::Scene *scene, Networking::NetworkManager *network_server)
    // {
    //     if (!CanCast(character->character_state))
    //     {
    //         return false;
    //     }
    //
    //     CharacterState::AddState(character->character_state, scene,
    //                              TimeUtils::GetTicksFromSeconds(character->definition->fire_rate),
    //                              CharacterState::State::Casting);
    //
    //     RigidbodyTransform rigidbody_data = character->rigidbody->GetRigidbodyTransform();
    //
    //     Projectile::Projectile *projectile = Projectile::CreateProjectile(
    //         scene, rigidbody_data, character->entity_metadata.entityId,
    //         character->definition->projectile_definition_id);
    //
    //     Networking::Message *message = network_server->GetEmptyMessage();
    //     MessageCreator::ProjectileFire(message, scene, projectile);
    //     network_server->SendAll(message, Networking::SendMode::Reliable);
    //
    //     return true;
    // }

} // namespace Novaland::Character
