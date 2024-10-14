////////////////////////////////////////////////////////////////////////////////
// File:        Input.h
// Author:      Bohumil Homola
// Date:        09/29/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Math/Vec2.h"

namespace Novaland::Input
{

enum InputKey : u8
{
    ATTACK = 1 << 0,
    SPECIAL_ABILITY_1 = 1 << 1,
    SPECIAL_ABILITY_2 = 1 << 2,
    SPECIFIC_1 = 1 << 3,
    SPECIFIC_2 = 1 << 4,
    SPECIFIC_3 = 1 << 5,
};

struct Input
{
    Vec2 movement_input = Vec2::ZERO();
    u8 keys = 0;
};

} // namespace Novaland::Input
