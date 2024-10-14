#pragma once

#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <string>

#ifdef __ANDROID__
#include "spdlog/sinks/android_sink.h"
#endif
#ifdef GODOT
#include <godot_cpp/variant/utility_functions.hpp>
#endif

#if defined UNITY_LOGGER && defined DEBUG_BUILD
#define UNITY_LOGGER_ENABLED
#endif

namespace Logger
{
extern std::shared_ptr<spdlog::logger> logger; // Just declare, do not define

void SetPrefix(const std::string &prefix);

void Info(const std::string &message);

template <typename... Args> void Info(spdlog::format_string_t<Args...> message, Args &&...args)
{
#ifdef __ANDROID__
    logger->info(message, std::forward<Args>(args)...);
#else
    spdlog::info(message, std::forward<Args>(args)...);
#endif

#if defined GODOT || defined UNITY_LOGGER_ENABLED
    spdlog::string_view_t string_view = spdlog::details::to_string_view(message);
    spdlog::memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), string_view, fmt::make_format_args(args...));
    std::string str(buf.data(), buf.size());
#endif

#ifdef GODOT
    std::string prepend = "[color=white]";
    std::string append = "[/color]";
    std::string godot_buffer = prepend + str + append;
    godot::UtilityFunctions::print_rich(godot_buffer.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
    Info(str);
#endif
}

void Warn(const std::string &message);

template <typename... Args> void Warn(spdlog::format_string_t<Args...> message, Args &&...args)
{
#ifdef __ANDROID__
    logger->warn(message, std::forward<Args>(args)...);
#else
    spdlog::warn(message, std::forward<Args>(args)...);
#endif
#if defined GODOT || defined UNITY_LOGGER_ENABLED
    spdlog::string_view_t string_view = spdlog::details::to_string_view(message);
    spdlog::memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), string_view, fmt::make_format_args(args...));
    std::string str(buf.data(), buf.size());
#endif

#ifdef GODOT
    std::string prepend = "[color=yellow]";
    std::string append = "[/color]";
    std::string godot_buffer = prepend + str + append;
    godot::UtilityFunctions::print_rich(godot_buffer.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
    Warn(str);
#endif
}

void Error(const std::string &message);

template <typename... Args> void Error(spdlog::format_string_t<Args...> message, Args &&...args)
{
#ifdef __ANDROID__
    logger->error(message, std::forward<Args>(args)...);
#else
    spdlog::error(message, std::forward<Args>(args)...);
#endif
#if defined GODOT || defined UNITY_LOGGER_ENABLED
    spdlog::string_view_t string_view = spdlog::details::to_string_view(message);
    spdlog::memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), string_view, fmt::make_format_args(args...));
    std::string str(buf.data(), buf.size());
#endif

#ifdef GODOT
    std::string prepend = "[color=red]";
    std::string append = "[/color]";
    std::string godot_buffer = prepend + str + append;
    godot::UtilityFunctions::print_rich(godot_buffer.c_str());
#endif

#ifdef UNITY_LOGGER_ENABLED
    Error(str);
#endif
}
void Debug(const std::string &message);

template <typename... Args> void Debug(spdlog::format_string_t<Args...> message, Args &&...args)
{
#ifdef __ANDROID__
    logger->debug(message, std::forward<Args>(args)...);
#else
    spdlog::debug(message, std::forward<Args>(args)...);
#endif
#ifdef GODOT
    spdlog::string_view_t string_view = spdlog::details::to_string_view(message);
    spdlog::memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), string_view, fmt::make_format_args(args...));
    godot::UtilityFunctions::printerr(buf.data());
#endif
}
} // namespace Logger
