////////////////////////////////////////////////////////////////////////////////
// File:        CharacterCollisionHnadeler.cpp
// Author:      Bohumil Homola
// Date:        10/02/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "CharacterCollisionHandler.h"
#include "DependencyInjector.h"
#include "Physics/CollisionListener.h"
#include "Physics/PhysicsWorld.h"

namespace Novaland::Character
{

CharacterCollisionHandler::CharacterCollisionHandler()
{
    m_world = Dependency::Get<Physics::PhysicsWorld>();
    m_projectile_container = Dependency::Get<Container<Projectile::ProjectileFramework>>();
    m_character_container = Dependency::Get<Container<CharacterFramework>>();

    m_world->collision_listener->AddOnCollisionEnterHandler(
        Entity::EntityType::CHARACTER, Entity::EntityType::PROJECTILE,
        [this](Physics::Rigidbody *character, Physics::Rigidbody *projectile,
               const Physics::IContactInfo &contact_info) {
            HandleCharacterProjectileCollision(character, projectile, contact_info);
        });
}

CharacterCollisionHandler::~CharacterCollisionHandler()
{
}

void CharacterCollisionHandler::HandleCharacterProjectileCollision(Physics::Rigidbody *character,
                                                                   Physics::Rigidbody *projectile,
                                                                   const Physics::IContactInfo &contact_info)
{
    CharacterFramework *character_framework = m_character_container->Get(character->entity->id);
    if (!character_framework)
    {
        bool isCharacter = character->entity->type == Entity::EntityType::CHARACTER;
        Logger::Error("Character not found ID: {} isCharacter: {}", character->entity->id, isCharacter);
    }

    Projectile::ProjectileFramework *projectile_framework = m_projectile_container->Get(projectile->entity->id);
    character_framework->m_hit_controller.HandleCharacterHit(projectile_framework, contact_info);
}

} // namespace Novaland::Character
