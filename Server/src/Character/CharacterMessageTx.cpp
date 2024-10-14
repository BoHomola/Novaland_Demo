////////////////////////////////////////////////////////////////////////////////
// File:        CharacterMessageTx.cpp
// Author:      Bohumil Homola
// Date:        10/01/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterMessageTx.h"
#include "DependencyInjector.h"
#include "GameTags.h"
#include "Networking/NetworkMessage.h"
#include "Physics/CollisionListener.h"
#include "Projectile/Projectile.h"
#include "Projectile/ProjectileFramework.h"
#include "SerServer.h"
#include "zpp_bits.h"

namespace Novaland::Character
{

CharacterMessageTx::CharacterMessageTx()
{
    Dependency::Register<CharacterMessageTx>(this);
    m_server_network_manager = Dependency::Get<Networking::ServerNetworkManager>();
    m_tick_manager = Dependency::Get<TickManager>();
}

CharacterMessageTx::~CharacterMessageTx()
{
    Dependency::Unregister<Networking::ServerNetworkManager>();
}

void CharacterMessageTx::SendCharacterStartFireMessage(u32 character_id)
{
    auto message = m_server_network_manager->GetEmptyOutcomingMessage();
    message->SetTag(GameTag::CHARACTER_FIRE_START);

    auto [data, out] = zpp::bits::data_out();
    Ser::CharacterFireStart characterFireStart{};
    characterFireStart.character_id = character_id;
    auto result = out(characterFireStart);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    m_server_network_manager->SendAll(message, Networking::SendMode::Reliable);
}

void CharacterMessageTx::SendCharacterFinishFireMessage(Character *character,
                                                        Projectile::ProjectileFramework *projectile,
                                                        const Vec2 &start_pos, f32 dir)
{
    auto message = m_server_network_manager->GetEmptyOutcomingMessage();
    message->SetTag(GameTag::CHARACTER_FIRE_FINISH);

    auto [data, out] = zpp::bits::data_out();
    Ser::CharacterFire characterFire;

    characterFire.tick = m_tick_manager->GetCurrentTick();
    characterFire.characterId = character->id;
    characterFire.definitionId = projectile->m_definition->definition_id;
    characterFire.projectileState.entityId = projectile->id;

    auto projectile_transform = projectile->m_projectile.rigidbody->GetTransform();
    characterFire.projectileState.position = {projectile_transform.position.x, projectile_transform.position.y};
    characterFire.projectileState.rotation = dir;

    auto result = out(characterFire);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    m_server_network_manager->SendAll(message, Networking::SendMode::Reliable);
}

void CharacterMessageTx::SendCharacterHitMessage(Character *character, Projectile::ProjectileFramework *projectile,
                                                 const Physics::IContactInfo &contact_info)
{
    auto message = m_server_network_manager->GetEmptyOutcomingMessage();
    message->SetTag(GameTag::CHARACTER_HIT);

    auto [data, out] = zpp::bits::data_out();
    Ser::CharacterHit characterHit{};

    characterHit.tick = m_tick_manager->GetCurrentTick();
    characterHit.damage = 0; // TEMP
    characterHit.characterId = character->id;
    characterHit.projectileId = projectile->id;
    auto conact_point = contact_info.GetContactPoint();
    characterHit.hitPosition = {conact_point.x, conact_point.y};
    characterHit.hitAngle = contact_info.GetHitAngle();

    auto result = out(characterHit);
    memcpy(message->GetMessagePtr(), data.data(), data.size());
    message->length = data.size();

    m_server_network_manager->SendAll(message, Networking::SendMode::Reliable);
}

} // namespace Novaland::Character
