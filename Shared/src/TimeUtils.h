#pragma once

#include "NovalandCommon.h"
#include <chrono>

namespace TimeUtils
{

static f32 timestamp = 20.0f;

inline f32 GetStepRate() 
{
    return 1.0f / timestamp;
}

inline void SetTimestamp(f32 newTimeStamp)
{
    timestamp = newTimeStamp;
}

inline u32 GetTicksFromSeconds(float seconds)
{
    return (u32)(seconds * timestamp);
}

inline f32 GetSecondsFromTicks(u32 ticks)
{
    return (float)ticks / timestamp;
}

inline u32 GetTicksFromMilliseconds(u32 milliseconds)
{
    return (u32)(milliseconds * timestamp / 1000.0f);
}

inline u32 GetMillisecondsFromTicks(u32 ticks)
{
    return (u32)(ticks * 1000.0f / timestamp);
}

inline i64 GetUtcNow()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return milliseconds.count();
}

} // namespace TimeUtils
