////////////////////////////////////////////////////////////////////////////////
// File:        ColliderDefinitions.h
// Author:      Bohumil Homola
// Date:        10/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <NovalandCommon.h>

namespace Novaland::Physics
{
struct Vertex
{
    f32 x;
    f32 y;
};

struct BoxColliderDefinition
{
    u32 id;
    f32 x = 0;
    f32 y = 0;
    f32 width = 0;
    f32 height = 0;
    f32 angle = 0;
};

struct CircleColliderDefinition
{
    u32 id;
    f32 x;
    f32 y;
    f32 radius;
};

struct PolygonColliderDefinition
{
    u32 id;
    f32 x;
    f32 y;
    std::vector<Vertex> vertices;
};

} // namespace Novaland::Physics
