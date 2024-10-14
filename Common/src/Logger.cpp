////////////////////////////////////////////////////////////////////////////////
// File:        Logger.cpp
// Author:      Bohumil Homola
// Date:        09/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Logger.h"

#ifdef UNITY_LOGGER_ENABLED
#include "UnityLogger/UnityLoggerC.h"
#endif
namespace Logger
{
#ifdef __ANDROID__
    std::shared_ptr<spdlog::logger> logger = spdlog::android_logger_mt("android", "NovalandLogger");
#endif

    void SetPrefix(const std::string &prefix)
    {
        spdlog::set_pattern("[%H:%M:%S.%e] [%^" + prefix + "%$] [%^%l%$] %v");
    }

    void Info(const std::string &message)
    {
#ifdef __ANDROID__
        logger->info(message.c_str());
#else
        spdlog::info(message.c_str());
#endif

#ifdef GODOT
        std::string prepend = "[color=white]";
        std::string append = "[/color]";
        std::string log_message = prepend + message + append;
        godot::UtilityFunctions::print_rich(log_message.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
        UNITY_LOG(unityLogPtr, message.c_str());
#endif
    }

    void Warn(const std::string &message)
    {
#ifdef __ANDROID__
        logger->warn(message.c_str());
#else
        spdlog::warn(message.c_str());
#endif
#ifdef GODOT
        std::string prepend = "[color=yellow]";
        std::string append = "[/color]";
        std::string log_message = prepend + message + append;
        godot::UtilityFunctions::print_rich(log_message.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
        UNITY_LOG_WARNING(unityLogPtr, message.c_str());
#endif
    }

    void Error(const std::string &message)
    {
#ifdef __ANDROID__
        logger->error(message.c_str());
#else
        spdlog::error(message.c_str());
#endif
#ifdef GODOT
        godot::UtilityFunctions::printerr(message.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
        UNITY_LOG_ERROR(unityLogPtr, message.c_str());
#endif
    }

    void Debug(const std::string &message)
    {
#ifdef __ANDROID__
        logger->debug(message.c_str());
#else
        spdlog::debug(message.c_str());
#endif
    }
} // namespace Logger
