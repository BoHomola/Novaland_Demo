cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG_BUILD)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(Novaland)

option(DISABLE_SERVER_GUI "Disable renderer in the project" OFF)
option(BUILD_SERVER "Build server" OFF)
option(BUILD_CLIENT "Build client with raylib GUI" OFF)
option(BUILD_GODOT "Build godot bindings" OFF)
option(PROFILER_ENABLED "Enable profiler" OFF)
option(BUILD_WRAPPER "Build C-style wrapper" OFF)

if(BUILD_WRAPPER)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(DISABLE_SERVER_GUI
    ${DISABLE_SERVER_GUI}
    CACHE BOOL "Disable renderer in the project")

set(PROFILER_ENABLED
    ${PROFILER_ENABLED}
    CACHE BOOL "Enable profiler")

add_subdirectory(libs/json)

if((NOT DISABLE_SERVER_GUI AND BUILD_SERVER) OR BUILD_CLIENT)
  add_subdirectory(libs/raylib)
endif()

set(SPDLOG_BUILD_PIC
    ON
    CACHE BOOL "Build position independent code (-fPIC)" FORCE)

set(BOX2D_BUILD_TESTBED
    OFF
    CACHE BOOL "Build the Box2D testbed" FORCE)
set(BOX2D_BUILD_UNIT_TESTS
    OFF
    CACHE BOOL "Build the Box2D unit tests" FORCE)

add_subdirectory(libs/box2d)
add_subdirectory(libs/spdlog)
add_subdirectory(libs/CLI11)
add_subdirectory(libs/cpptrace)
add_subdirectory(libs/zpp_bits)

set(ENET_STATIC TRUE)
add_subdirectory(libs/enet)

set(CURL_USE_OPENSSL OFF)
set(CURL_STATICLIB ON)
set(BUILD_CURL_EXE OFF)
set(CURL_DISABLE_TESTS ON)
add_subdirectory(libs/curl)

if(PROFILER_ENABLED)
  add_subdirectory(libs/tracy)
endif()

add_subdirectory(Common)
add_subdirectory(Shared)
add_subdirectory(SerializationFiles)

if(BUILD_GODOT
   OR BUILD_CLIENT
   OR BUILD_WRAPPER)
  add_subdirectory(Client)
endif()

if(BUILD_WRAPPER)
  add_subdirectory(ClientFlat)
endif()

if(BUILD_GODOT)
  add_subdirectory(libs/godot-cpp)
  add_subdirectory(GDClientSrc)
endif()

if(BUILD_SERVER)
  add_subdirectory(Server)
endif()

if(BUILD_CLIENT)
  add_subdirectory(ClientGui)
  add_subdirectory(ClientMock)
endif()
