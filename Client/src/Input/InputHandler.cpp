////////////////////////////////////////////////////////////////////////////////
// File:        InputHandler.cpp
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "InputHandler.h"
#include "DependencyInjector.h"
#include "Input/Input.h"
#include "Logger.h"
#include "Math/Math.h"
#include "Math/Vec2.h"

namespace Novaland
{
    InputHandler::InputHandler(InputType type)
    {
        Dependency::Register<InputHandler>(this);
        this->ChangeType(type);
        m_keyboard_input = Vec2::ZERO();
        m_joystick_input = Vec2::ZERO();
        m_keys = 0;
    }

    InputHandler::~InputHandler()
    {
        Dependency::Unregister<InputHandler>();
    }

    void InputHandler::ChangeType(InputType type)
    {
        m_type = type;
    }

    void InputHandler::SetKeyboardInput(Vec2 input)
    {
        m_keyboard_input = input;
    }

    void InputHandler::SetJoystickInput(Vec2 input)
    {
        m_joystick_input = input;
    }

    void InputHandler::SetSecondaryJoystickInput(Vec2 input)
    {
        m_secondary_joystick_input = input;
    }

    void InputHandler::SetKeys(u8 keys)
    {
        this->m_keys = keys;
    }

    Input::Input InputHandler::GetInput(f32 character_rotation) const
    {
        Input::Input input;
        input.keys = m_keys;

        if (m_keyboard_input != Vec2::ZERO())
        {
            input.movement_input = m_keyboard_input;
        }

        if (m_joystick_input != Vec2::ZERO())
        {
            input.movement_input = m_joystick_input.Normalized();
            input.movement_input.y = -input.movement_input.y;
            f32 inputAngle =
                Math::NormalizeAngle(Math::Rad2Deg(Math::Atan2(input.movement_input.y, input.movement_input.x)) - 90);
            f32 characterAngle = Math::NormalizeAngle(Math::Rad2Deg(character_rotation));

            f32 diff = characterAngle - inputAngle;
            if (diff < -180)
                diff += 360;
            if (diff > 180)
                diff -= 360;

            if (Math::Abs(diff) > 35)
            {
                input.movement_input.x = diff > 0 ? 1 : -1;
            }
            else
            {
                input.movement_input.x = diff / 35;
            }

            f32 length = Math::Sqrt(m_joystick_input.x * m_joystick_input.x + m_joystick_input.y * m_joystick_input.y);
            length = Math::Clamp(length, 0.0f, 1.0f);
            input.movement_input.y = length;
        }
        if (m_secondary_joystick_input != Vec2::ZERO())
        {
            // input.movement_input.x = -m_secondary_joystick_input.x;

            f32 inputAngle = Math::NormalizeAngle(
                Math::Rad2Deg(Math::Atan2(-m_secondary_joystick_input.y, m_secondary_joystick_input.x)) - 90);
            f32 characterAngle = Math::NormalizeAngle(Math::Rad2Deg(character_rotation));
            f32 diff = characterAngle - inputAngle;
            if (diff < -180)
                diff += 360;
            if (diff > 180)
                diff -= 360;

            if (Math::Abs(diff) > 35)
            {
                input.movement_input.x = diff > 0 ? 1 : -1;
            }
            else
            {
                input.movement_input.x = diff / 35;
            }
        }

        return input;
    }
} // namespace Novaland
