#pragma once

#include "Logger.h"
#ifdef PROFILER_ENABLED
#include "tracy/Tracy.hpp"
#ifndef TRACY_ENABLE
#define TRACY_ENABLE
#endif
#endif
#include <functional>
#include <limits>
#include <mutex>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef DEBUG_BUILD
#include "DebugStackTrace.h"
#include <cassert>
#endif
#define TIMER_START std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
#define TIMER_END                                                                                                      \
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();                     \
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();                            \
    Logger::Info("Time: {0}us", duration);

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef unsigned char byte;
typedef std::size_t size_t;

#ifdef PROFILER_ENABLED
#define PROFILE_SCOPE ZoneScoped;
#define PROFILE_NEW_FRAME FrameMark;
#else
#define PROFILE_SCOPE ;
#define PROFILE_NEW_FRAME ;
#endif
