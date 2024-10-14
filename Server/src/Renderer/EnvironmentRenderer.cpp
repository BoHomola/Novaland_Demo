#ifndef DISABLE_SERVER_GUI
#include "EnvironmentRenderer.h"
#include "Math/Math.h"
#include "Math/Vec2.h"
#include "NovalandServer.h"
#include "Physics/Map.h"
#include "Player/ServerPlayer.h"
#include "raylib.h"
#include "rlgl.h"
#include <string>

namespace Novaland::Renderer
{

const int screenWidth = 1000;
const int screenHeight = 1000;

Vector2 FlipY(Vector2 pos)
{
    pos.y = pos.y;
    return pos;
}

void DrawPlayerDetails(Player::ServerPlayer *player, Font &font, Vector2 topLeft, int playerIndex,
                       Container<Character::CharacterFramework> *character_container)
{
    auto character_framework = character_container->Get(player->character_id);

    el_DrawTextEx(font, ("Player:" + std::to_string(character_framework->id)).c_str(),
               FlipY({topLeft.x + 150 * playerIndex, topLeft.y}), 24, 1, WHITE);
    el_DrawTextEx(font, ("Ping :" + std::to_string(player->player_connection->peer->roundTripTime)).c_str(),
               FlipY({topLeft.x + 150 * playerIndex, topLeft.y - 24}), 24, 1, WHITE);

    Novaland::Vec2 positionN = character_framework->m_character.rigidbody->GetPosition();
    el_DrawTextEx(font, ("X: " + std::to_string(positionN.x)).c_str(),
               FlipY({topLeft.x + 150 * playerIndex, topLeft.y - 48}), 24, 1, WHITE);
    el_DrawTextEx(font, ("Y: " + std::to_string(positionN.y)).c_str(),
               FlipY({topLeft.x + 150 * playerIndex, topLeft.y - 72}), 24, 1, WHITE);
}

void DrawEntities(NovalandServer *server)
{
    for (Character::CharacterFramework *character_framework : server->character_container->GetAll())
    {
        f32 radius = character_framework->definition->collider_definition.radius;
        Vector2 position = FlipY({character_framework->m_character.rigidbody->GetPosition().x,
                                  character_framework->m_character.rigidbody->GetPosition().y});
        DrawCircleV(position, radius, YELLOW);
    }

    for (Projectile::ProjectileFramework *projectile : server->projectile_container->GetAll())
    {
        f32 radius = projectile->m_definition->collider_definition.radius;
        Vec2 pos = projectile->m_projectile.rigidbody->GetPosition();
        Vector2 position = FlipY({pos.x, pos.y});
        DrawCircleV(position, radius, GREEN);
    }
}
void DrawMap(Map *map)
{
    for (Physics::BoxColliderDefinition &collider : map->box_colliders)
    {
        rl_Rectangle box = {collider.x, collider.y, collider.width * 2, collider.height * 2};
        DrawRectanglePro(box, Vector2{collider.width, collider.height}, Math::Rad2Deg(collider.angle), WHITE);
    }
}

void RenderWorld(NovalandServer *server, Map *map)
{
    TickManager *tick_manager = Dependency::Get<TickManager>();
    Logger::Info("Rendering world.");
    InitWindow(screenWidth, screenHeight, "Novaland World");
    SetTargetFPS(60);

    Camera2D m_camera = {0};
    m_camera.target = (Vector2){0.0f, 0.0f};
    m_camera.offset = (Vector2){1000 / 2.0f, (1000 / 2.0f) + 200};
    m_camera.zoom = 10.0f;

    Font font = LoadFont("Geologica-Medium.ttf");

    if (!font.texture.id)
    {
        Logger::Error("Could not load font");
        return;
    }

    Vector2 topLeft = {0.0f, 0.0f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        // text
        int playerIndex = 1;
        for (auto player : server->player_container->GetAll())
        {
            DrawPlayerDetails(player, font, topLeft, playerIndex, server->character_container);
            playerIndex++;
        }
        el_DrawTextEx(font, ("Tick: " + std::to_string(tick_manager->GetCurrentTick())).c_str(), topLeft, 32, 1, WHITE);

        BeginMode2D(m_camera);
        DrawEntities(server);
        DrawMap(map);

        EndMode2D();
        EndDrawing();
    }

    UnloadFont(font);
    rl_CloseWindow();
}
} // namespace Novaland::Renderer
#endif // NOVALAND_DISABLE_RENDERER
