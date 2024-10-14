////////////////////////////////////////////////////////////////////////////////
// File:        PlayerMessageTx.cpp
// Author:      Bohumil Homola
// Date:        09/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "PlayerMessageTx.h"
#include "Networking/NetworkMessage.h"
#include "SerServer.h"

namespace Novaland::Player
{

void PlayerMessageTx::NewPlayer(ServerPlayer *player)
{

    auto message = network_manager->GetEmptyOutcomingMessage();
    message->SetTag(GameTag::NEW_PLAYER);

    auto [data, out] = zpp::bits::data_out();
    Ser::PlayerDefinition newPlayer;
    newPlayer.playerId = player->id;

    auto character_framework = character_container->Get(player->character_id);

    newPlayer.characterDefinition.health = character_framework->m_character.health;
    newPlayer.characterDefinition.characterId = character_framework->id;
    newPlayer.characterDefinition.characterDefinitionId = character_framework->definition->definition_id;

    Vec2 characterPosition = character_framework->m_character.rigidbody->GetPosition();
    newPlayer.characterDefinition.transform.position.x = characterPosition.x;
    newPlayer.characterDefinition.transform.position.y = characterPosition.y;

    newPlayer.characterDefinition.transform.angularVelocity =
        character_framework->m_character.rigidbody->GetAngularVelocity();
    Vec2 characterVelocity = character_framework->m_character.rigidbody->GetLinearVelocity();
    newPlayer.characterDefinition.transform.velocity.x = characterVelocity.x;
    newPlayer.characterDefinition.transform.velocity.y = characterVelocity.y;
    newPlayer.characterDefinition.transform.rotation = character_framework->m_character.rigidbody->GetAngle();

    auto result = out(newPlayer);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    network_manager->SendAll(message, player->player_connection, Networking::SendMode::Reliable);
}
} // namespace Novaland::Player
