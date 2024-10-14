////////////////////////////////////////////////////////////////////////////////
// File:        Application.h
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Physics/PhysicsWorld.h"
#include "Window.h"

namespace Novaland
{
class Application
{
  public:
    ~Application();
    void Init(i32 width, i32 height);
    void Run();
    void Update(float delta_time);
    void FixedUpdate();

  private:
    Novaland::Vec2 GetKeyMovementInput();
    Novaland::Vec2 GetJoystickMovementInput(f32 character_rotation);
    u8 GetKeyInput();

  private:
    Window m_window;

  private:
    Client *p_client;
};

} // namespace Novaland
