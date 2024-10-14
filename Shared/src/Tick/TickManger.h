////////////////////////////////////////////////////////////////////////////////
// File:        TickManger.h
// Author:      Bohumil Homola
// Date:        08/30/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "DependencyInjector.h"
#include "NovalandCommon.h"

namespace Novaland
{

class TickManager
{
  public:
    TickManager()
    {
        Dependency::Register<TickManager>(this);
        Initialize();
    }
    ~TickManager()
    {
        Dependency::Unregister<TickManager>();
    }

    void Initialize()
    {
        m_tick = 0;
    }
    void IncreaseTick()
    {
        m_tick++;
    }
    u32 GetCurrentTick() const
    {
        return m_tick;
    }

    u64 GetTickUTC() const
    {
        return first_tick_UTC + m_tick;
    }

    u64 GetFirstTickUTC() const
    {
        return first_tick_UTC;
    }

    void SetFirstTickUTC(u64 tick)
    {
        first_tick_UTC = tick;
    }

    f32 GetDeltaTime() const
    {
        return fixed_delta_time;
    }
    void SetDeltaTime(f32 delta_time)
    {
        fixed_delta_time = delta_time;
    }

  private:
    u32 m_tick;
    u64 first_tick_UTC;
    f32 fixed_delta_time;
};

} // namespace Novaland
