////////////////////////////////////////////////////////////////////////////////
// File:        Vec2.h
// Author:      Bohumil Homola
// Date:        09/06/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Math/Math.h"
#include "NovalandCommon.h"
#include <math.h>

namespace Novaland
{
struct Vec2
{
    f32 x = 0;
    f32 y = 0;

    Vec2() : x(0), y(0)
    {
    }
    Vec2(f32 x, f32 y) : x(x), y(y)
    {
    }

    Vec2 operator+(const Vec2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return {x - other.x, y - other.y};
    }

    Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    Vec2 operator*(f32 other) const
    {
        return {x * other, y * other};
    }

    Vec2 operator/(f32 other) const
    {
        return {x / other, y / other};
    }

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2 &other) const
    {
        return x != other.x || y != other.y;
    }

    f32 Dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    f32 Cross(const Vec2 &other) const
    {
        return x * other.y - y * other.x;
    }

    f32 Magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    f32 AngleBetween(const Vec2 &other) const
    {
        return acos(this->Dot(other) / (this->Magnitude() * other.Magnitude()));
    }

    f32 MagnitudeSquared() const
    {
        return x * x + y * y;
    }

    Vec2 Normalized() const
    {
        return *this / this->Magnitude();
    }

    f32 Distance(const Vec2 &other) const
    {
        return (*this - other).Magnitude();
    }

    f32 ToAngle() const
    {
        return atan2(y, x);
    }

    f32 ToB2Angle() const
    {
        return atan2(y, x) + Math::Pi * 0.5f;
    }

    Vec2 Reflect(const Vec2 &normal) const
    {
        return *this - normal * 2 * this->Dot(normal);
    }

    Vec2 Perpendicular() const
    {
        return {-y, x};
    }

    static Vec2 Lerp(const Vec2 &a, const Vec2 &b, f32 t)
    {
        return a + (b - a) * t;
    }

    static Vec2 Smoothstep(const Vec2 &a, const Vec2 &b, f32 t)
    {
        return a + (b - a) * (3 * t * t - 2 * t * t * t);
    }

    static Vec2 Slerp(const Vec2 &a, const Vec2 &b, f32 t)
    {
        f32 theta = a.AngleBetween(b);
        return a * sin((1 - t) * theta) / sin(theta) + b * sin(t * theta) / sin(theta);
    }

    static Vec2 ZERO()
    {
        return {0, 0};
    }

    static Vec2 FromRadian(f32 angle)
    {
        return {cos(angle), sin(angle)};
    }

    static Vec2 FromDegree(f32 angle)
    {
        return FromRadian(Math::Rad2Deg(angle));
    }
};
}; // namespace Novaland
