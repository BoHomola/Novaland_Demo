////////////////////////////////////////////////////////////////////////////////
// File:        Math.h
// Author:      Bohumil Homola
// Date:        09/08/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include <cmath>

namespace Novaland::Math
{

f32 constexpr Epsilon = 0.0001f;
f32 constexpr Pi = 3.14159265358979323846f;

inline f32 Lerp(f32 a, f32 b, f32 t)
{
    return a + (b - a) * t;
}

inline f32 Abs(f32 a)
{
    return a < 0 ? -a : a;
}

inline f32 Sqrt(f32 a)
{
    return std::sqrt(a);
}

inline f32 Sin(f32 a)
{
    return std::sin(a);
}

inline f32 Cos(f32 a)
{
    return std::cos(a);
}

inline f32 Tan(f32 a)
{
    return std::tan(a);
}

inline f32 Asin(f32 a)
{
    return std::asin(a);
}

inline f32 Acos(f32 a)
{
    return std::acos(a);
}

inline f32 Atan(f32 a)
{
    return std::atan(a);
}

inline f32 Atan2(f32 a, f32 b)
{
    return std::atan2(a, b);
}

inline f32 constexpr Rad2Deg(f32 a)
{
    return a * 180.0f / Pi;
}

inline constexpr f32 Deg2Rad(f32 a)
{
    return a * 3.14159265358979323846f / 180.0f;
}

inline f32 NormalizeAngle(f32 angle)
{
    angle = std::fmod(angle, 360.0f);
    if (angle < 0)
    {
        angle += 360;
    }

    return angle;
}

inline f32 Clamp(f32 value, f32 min, f32 max)
{
    return value < min ? min : value > max ? max : value;
}

} // namespace Novaland::Math
