////////////////////////////////////////////////////////////////////////////////
// File:        InputHandlerC.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include "Export.h"
#include "Math/Vec2.h"

EXPORT void SetKeyboardInput(Novaland::Client *client, Novaland::Vec2 input)
{
    client->input_handler->SetKeyboardInput(input);
}

EXPORT void SetJoystickInput(Novaland::Client *client, Novaland::Vec2 input)
{
    client->input_handler->SetJoystickInput(input);
}

EXPORT void SetKeys(Novaland::Client *client, u8 keys)
{
    client->input_handler->SetKeys(keys);
}
