////////////////////////////////////////////////////////////////////////////////
// File:        Export.h
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT extern "C" __declspec(dllexport)
#elif defined(__APPLE__) && defined(__MACH__) || defined(__linux__) || defined(__ANDROID__) || defined(__SWITCH__)
#define EXPORT extern "C" __attribute__((visibility("default")))
#else
#error "Unknown platform"
#endif
