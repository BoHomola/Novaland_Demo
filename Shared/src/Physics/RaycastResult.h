////////////////////////////////////////////////////////////////////////////////
// File:        RaycastResult.h
// Author:      Bohumil Homola
// Date:        10/17/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "Logger.h"
#include "Math/Vec2.h"
#include "NovalandCommon.h"
#include "Physics/Categories.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world_callbacks.h"

namespace Novaland::Physics
{
struct RaycastHit
{
    bool hit = false;
    Vec2 point;
    Vec2 normal;
    f32 fraction = 1.0f;
    b2Fixture *fixture = nullptr;
};

struct RaycastResult : b2RayCastCallback
{
    std::vector<RaycastHit> hits;
    u16 mask_bits;
    f32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, f32 fraction) override
    {
        if (mask_bits & fixture->GetFilterData().categoryBits)
        {
            RaycastHit &hit_info = hits.emplace_back();
            hit_info.hit = true;
            hit_info.point = {point.x, point.y};
            hit_info.normal = {normal.x, normal.y};
            hit_info.fraction = fraction;
            hit_info.fixture = fixture;
        }
        return 1.0;
    }
};

struct RaycastClosestResult : b2RayCastCallback
{
    RaycastHit hit_info;
    u16 mask_bits;

    f32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, f32 fraction) override
    {
        if (fraction < hit_info.fraction && mask_bits & fixture->GetFilterData().categoryBits)
        {
            hit_info.fraction = fraction;
            hit_info.point = {point.x, point.y};
            hit_info.normal = {normal.x, normal.y};
            hit_info.hit = true;
            hit_info.fixture = fixture;
        }
        return 1.0;
    }
};

struct RaycastRadiusResult
{
    bool hit = false;
    Vec2 origin_point;
    Vec2 hit_point;
    Vec2 normal;
    b2Fixture *fixture = nullptr;
};

} // namespace Novaland::Physics
