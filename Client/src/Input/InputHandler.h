////////////////////////////////////////////////////////////////////////////////
// File:        InputHandler.h
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Input/Input.h"
#include "Input/InputType.h"
#include "Math/Vec2.h"

namespace Novaland
{

class InputHandler
{
  public:
    InputHandler(InputType type);
    ~InputHandler();
    void ChangeType(InputType type);
    void HandleMovement(Vec2 input);
    Input::Input GetInput(f32 character_rotation) const;

    void SetKeyboardInput(Vec2 input);
    void SetJoystickInput(Vec2 input);
    void SetSecondaryJoystickInput(Vec2 input);
    void SetKeys(u8 keys);

  private:
    Vec2 m_keyboard_input;
    Vec2 m_joystick_input;
    Vec2 m_secondary_joystick_input;
    u8 m_keys;

    InputType m_type;
};
} // namespace Novaland
