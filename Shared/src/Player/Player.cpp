#include "Player.h"

namespace Novaland::Player
{

    // Player::Player()
    // {
    // }
    //
    // Player::~Player()
    // {
    // }

    // void HandleCharacterFire(Player *player, Networking::Message *message, ServerContext &context)
    // {
    //     CurrentSceneData currentSceneData = context.scene->GetCurrentSceneData();
    //     Scene::Scene *scene = context.scene;
    //     bool result = Character::CharacterFire(player->character, scene, context.network_server);
    // }

    // void UpdatePlayer(Player *player, Scene::Scene *scene)
    // {
    //     if (player->player_input_queue.IsEmpty())
    //     {
    //         return;
    //     }
    //
    //     PlayerInput::Reader playerInput = player->player_input_queue.Pop();
    //     while (playerInput.getTick() < player->client_tick)
    //     {
    //         if (player->player_input_queue.IsEmpty())
    //         {
    //             return;
    //         }
    //         playerInput = player->player_input_queue.Pop();
    //     }
    //
    //     player->client_tick = playerInput.getTick();
    //     player->character->player_input_queue.Push(b2Vec2(playerInput.getX(), playerInput.getY()));
    //
    //     // CurrentSceneData currentSceneData = Scene::GetCurrentSceneData(scene);
    //     // Character::UpdateCharacter(player->character, currentSceneData);
    // }

} // namespace Novaland::Player
