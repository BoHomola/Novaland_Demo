////////////////////////////////////////////////////////////////////////////////
// File:        Window.cpp
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Window.h"
#include "Base/Component/Container.h"
#include "Character/Character.h"
#include "Character/CharacterContainer.h"
#include "Client.h"
#include "Logger.h"
#include "Physics/PhysicsWorld.h"
#include "raylib.h"

namespace Novaland
{
void Window::Init(i32 width, i32 height)
{
    f32 multiplier = 1;
    m_width = width * multiplier;
    m_height = height * multiplier;
    InitWindow(m_width, m_height, "Novaland Client");
    SetTargetFPS(0);

    m_camera = {0};
    m_camera.target = (Vector2){0.0f, 0.0f};
    m_camera.offset = (Vector2){m_width / 2.0f, (m_height / 2.0f) + 50};
    m_camera.rotation = 0.0f;
    m_camera.zoom = 15.0f * multiplier;

    font = LoadFont("Geologica-Medium.ttf");
    if (!font.texture.id)
    {
        Logger::Error("Could not load font");
        return;
    }
}

void Window::Render(Physics::PhysicsWorld *world, Container<Novaland::Player::ClientPlayer> *player_container,
                    Character::CharacterContainer *character_container, Client *client)
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(m_camera);
    if (client->game_initialized)
    {

        EndMode2D();
        el_DrawTextEx(font, ("RTT: " + std::to_string(client->m_connection->peer->roundTripTime)).c_str(), {20, 0}, 24, 1,
                   WHITE);
        el_DrawTextEx(font, ("Packet Loss: " + std::to_string(client->m_connection->peer->packetLoss)).c_str(), {20, 26},
                   24, 1, WHITE);

        el_DrawTextEx(
            font,
            ("Outgoing Bandwith: " + std::to_string(client->m_connection->peer->outgoingBandwidth) + "b/s").c_str(),
            {20, 52}, 24, 1, WHITE);
        el_DrawTextEx(
            font,
            ("Incoming Bandwith: " + std::to_string(client->m_connection->peer->incomingBandwidth) + "b/s").c_str(),
            {20, 78}, 24, 1, WHITE);

        Vec2 Position = client->character_container->own_character->m_character.rigidbody->GetPosition();
        el_DrawTextEx(font, ("X: " + std::to_string(Position.x)).c_str(), {300, 0}, 24, 1, WHITE);
        el_DrawTextEx(font, ("Y: " + std::to_string(Position.y)).c_str(), {300, 24}, 24, 1, WHITE);
        BeginMode2D(m_camera);

        for (auto collider : world->m_map->box_colliders)
        {
            // Rectangle box = {collider.x - collider.width, collider.y - collider.height, collider.width * 2,
            //                  collider.height * 2};
            // DrawRectangleRec(box, WHITE);
            rl_Rectangle box = {collider.x, collider.y, collider.width * 2, collider.height * 2};
            // DrawRectangleRec(box, WHITE);
            DrawRectanglePro(box, Vector2{collider.width, collider.height}, Math::Rad2Deg(collider.angle), WHITE);
        }

        for (auto &character : character_container->GetAll())
        {
            f32 radius = character->definition->collider_definition.radius;
            Vector2 position = {character->m_interpolator.interpolated_transform.position.x,
                                character->m_interpolator.interpolated_transform.position.y};
            if (character->is_own)
            {
                DrawCircleV(position, radius, BLUE);
            }
            else
            {
                DrawCircleV(position, radius, YELLOW);
            }
        }

        for (Projectile::ProjectileFramework *projectile : client->projectile_container->GetAll())
        {
            f32 radius = projectile->m_definition->collider_definition.radius;
            auto pos = projectile->m_interpolator.interpolated_transform.position;
            Vector2 position = {pos.x, pos.y};
            DrawCircleV(position, radius, RED);
        }
    }
    else
    {
        EndMode2D();
        el_DrawTextEx(font, "Not Connected", {(m_width / 2) - 100.0f, m_height / 2.0f}, 32, 1, WHITE);
        BeginMode2D(m_camera);
    }

    EndMode2D();

    EndDrawing();
}
} // namespace Novaland
