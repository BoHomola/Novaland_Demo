////////////////////////////////////////////////////////////////////////////////
// File:        Event.h
// Author:      Bohumil Homola
// Date:        10/22/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
namespace Novaland::Event
{
struct Event
{
  public:
    u32 fire_tick;

    bool operator<(const Event &other) const
    {
        return fire_tick > other.fire_tick;
    }
    std::function<void()> callback;
};

} // namespace Novaland::Event
