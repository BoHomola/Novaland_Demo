////////////////////////////////////////////////////////////////////////////////
// File:        GameController.cpp
// Author:      Bohumil Homola
// Date:        09/21/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "GameController.h"
#include "Character/OwnCharacterFramework.h"
#include "DependencyInjector.h"
#include "Math/Vec2.h"
#include "Physics/Rigidbody.h"

namespace Novaland::Game
{

GameController::GameController()
{
    Dependency::Register<GameController>(this);
    character_container = Dependency::Get<Character::CharacterContainer>();
}

void GameController::UpdateGameState(const Ser::GameStateUpdate &game_state_update)
{
    PROFILE_SCOPE
    for (auto characterUpdate : game_state_update.characters)
    {
        auto character = character_container->Get(characterUpdate.characterId);

        if (character == nullptr)
        {
            continue;
        }

        Vec2 position = {characterUpdate.transform.position.x, characterUpdate.transform.position.y};
        Vec2 linear_velocity = {characterUpdate.transform.velocity.x, characterUpdate.transform.velocity.y};

        if (character->is_own)
        {
            Character::OwnCharacterFramework *own_character = character_container->own_character;
            Physics::Transform transform = {position, characterUpdate.transform.rotation};
            Physics::Velocity velocity = {linear_velocity, characterUpdate.transform.angularVelocity};
            own_character->m_reconciliation_component.ReconcileCharacter(game_state_update.clientTick, transform,
                                                                         velocity);
        }
        else
        {
            character->m_character.rigidbody->SetTransform(position, characterUpdate.transform.rotation);
        }
    }
}
} // namespace Novaland::Game
