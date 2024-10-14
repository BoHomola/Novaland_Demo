////////////////////////////////////////////////////////////////////////////////
// File:        Window.h
// Author:      Bohumil Homola
// Date:        08/19/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Base/Component/Container.h"
#include "Character/CharacterContainer.h"
#include "Client.h"
#include "Physics/PhysicsWorld.h"
#include "raylib.h"
#include <NovalandCommon.h>

namespace Novaland
{
class Window
{
  public:
    void Init(i32 width, i32 height);
    void Render(Physics::PhysicsWorld *world, Container<Novaland::Player::ClientPlayer> *player_container,
                Character::CharacterContainer *character_container, Novaland::Client *client);

  private:
    i32 m_width;
    i32 m_height;
    Camera2D m_camera;
    Font font;
};
} // namespace Novaland
