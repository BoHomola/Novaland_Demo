#include "Map.h"
#include "Math/Math.h"
#include <box2d/b2_polygon_shape.h>

namespace Novaland
{

Map *CreateMap()
{
    Map *map = new Map;
    // top and bottom row
    for (float i = -35.0f; i <= 35.0f; i += 10.0f)
    {
        f32 width = 10.0f / 2;
        f32 height = 1.0f / 2;

        Physics::BoxColliderDefinition objectDefTop;
        objectDefTop.x = i;
        objectDefTop.y = 20;
        objectDefTop.width = width;
        objectDefTop.height = height;

        Physics::BoxColliderDefinition objectDefBot;
        objectDefBot.x = i;
        objectDefBot.y = -20;
        objectDefBot.width = 10.0f / 2;
        objectDefBot.height = 1.0f / 2;

        map->box_colliders.push_back(objectDefTop);
        map->box_colliders.push_back(objectDefBot);
    }

    // left and right column
    for (f32 i = -15.0f; i <= 15.0f; i += 10.0f)
    {
        f32 width = 1.0f / 2;
        f32 height = 10.0f / 2;

        Physics::BoxColliderDefinition objectDefLeft;
        objectDefLeft.x = -40;
        objectDefLeft.y = i;
        objectDefLeft.width = width;
        objectDefLeft.height = height;

        Physics::BoxColliderDefinition objectDefRight;
        objectDefRight.x = 40;
        objectDefRight.y = i;
        objectDefRight.width = width;
        objectDefRight.height = height;

        map->box_colliders.push_back(objectDefLeft);
        map->box_colliders.push_back(objectDefRight);
    }

    // left middle
    for (f32 i = -5.0f; i <= 15.0f; i += 10.0f)
    {
        Physics::BoxColliderDefinition objectDefLeft;
        objectDefLeft.x = -10;
        objectDefLeft.y = i;
        objectDefLeft.width = 1.0f / 2;
        objectDefLeft.height = 10.0f / 2;

        map->box_colliders.push_back(objectDefLeft);
    }

    // right middle
    for (f32 i = -15.0f; i <= 5.0f; i += 10.0f)
    {
        Physics::BoxColliderDefinition objectDefLeft;
        objectDefLeft.x = 10;
        objectDefLeft.y = i;
        objectDefLeft.width = 1.0f / 2;
        objectDefLeft.height = 10.0f / 2;

        map->box_colliders.push_back(objectDefLeft);
    }

    Physics::BoxColliderDefinition angled_wall;
    angled_wall.x = 25;
    angled_wall.y = 0;
    angled_wall.width = 1.0f / 2;
    angled_wall.height = 10.0f / 2;
    angled_wall.angle = Math::Deg2Rad(45.0f);

    map->box_colliders.push_back(angled_wall);

    return map;
}

} // namespace Novaland
