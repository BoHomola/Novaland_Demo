#pragma once

#include "NovalandCommon.h"

namespace Novaland
{
enum GameTag : u16
{
    // Server tags
    GAME_STATE_SYNC = 10,
    GAME_STATE_UPDATE = 20,
    NEW_PLAYER = 50,
    PLAYER_DISCONNECTED = 51,
    CHARACTER_FIRE_START = 59,
    CHARACTER_FIRE_FINISH = 60,
    CHARACTER_HIT = 70,

    // Client Tags
    PING = 900,
    PLAYER_MOVEMENT_INPUT = 1000,
    PLAYER_KEY_INPUT = 1001,
    CHARACTER_FIRE_REQUEST = 1010,
};

} // namespace Novaland
