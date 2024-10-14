#pragma once

#include "ColliderDefinitions.h"
#include <NovalandCommon.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_shape.h>

namespace Novaland
{

struct Map
{
    std::vector<Physics::BoxColliderDefinition> box_colliders;
    std::vector<Physics::CircleColliderDefinition> circle_colliders;
    std::vector<Physics::PolygonColliderDefinition> polygon_colliders;
};

Map *CreateMap();
} // namespace Novaland
