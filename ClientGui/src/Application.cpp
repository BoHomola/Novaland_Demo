////////////////////////////////////////////////////////////////////////////////
// File:        Application.cpp
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "raylib.h"

using namespace Novaland;

void Application::Init(i32 width, i32 height)
{
    m_window.Init(width, height);
    p_client = new Client();
    p_client->Connect("127.0.0.1", 5600);
}

Novaland::Vec2 Application::GetKeyMovementInput()
{
    Novaland::Vec2 input_vec = {0, 0};
    if (IsKeyDown(KEY_W))
    {
        input_vec.y = 1;
    }
    if (IsKeyDown(KEY_A))
    {
        input_vec.x = 1;
    }
    if (IsKeyDown(KEY_D))
    {
        input_vec.x = -1;
    }
    return input_vec;
}

Novaland::Vec2 Application::GetJoystickMovementInput(f32 character_rotation)
{
    return Vec2::ZERO();
}

u8 Application::GetKeyInput()
{
    u8 keys = 0;
    if (IsKeyDown(KEY_SPACE))
    {
        keys |= Novaland::Input::InputKey::ATTACK;
    }

    if (IsKeyDown(KEY_F))
    {
        keys |= Novaland::Input::InputKey::SPECIAL_ABILITY_2;
    }

    return keys;
}

void Application::Run()
{
}

void Application::Update(float delta_time)
{
    p_client->input_handler->SetKeys(GetKeyInput());
    p_client->input_handler->SetKeyboardInput(GetKeyMovementInput());
    m_window.Render(p_client->world, p_client->player_container, p_client->character_container, p_client);
    // raylibs delta time in miliseconds

    p_client->Update(delta_time);
}

void Application::FixedUpdate()
{
    p_client->FixedUpdate();
}

Application::~Application()
{
    delete p_client;
}
