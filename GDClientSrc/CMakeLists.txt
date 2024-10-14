cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GDNovalandClient)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

if(ANDROID)
  add_definitions(-D__ANDROID__)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE NovalandClient)

target_link_libraries(${PROJECT_NAME} PRIVATE godot-cpp)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # OR "${CMAKE_CXX_COMPILER_ID}
                                                # STREQUAL "GNU")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Output and library name

# Determine the current platform
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CURRENT_PLATFORM "linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
  set(CURRENT_PLATFORM "android")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CURRENT_PLATFORM "macos")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(CURRENT_PLATFORM "windows")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
  set(CURRENT_PLATFORM "ios")
else()
  set(CURRENT_PLATFORM ${CMAKE_SYSTEM_NAME})
endif()

# The architecture
set(CURRENT_ARCH ${CMAKE_SYSTEM_PROCESSOR})

if(NOT CMAKE_BUILD_TYPE)
  set(CURRENT_BUILD_TYPE "debug")
else()
  string(TOLOWER ${CMAKE_BUILD_TYPE} CURRENT_BUILD_TYPE)
endif()

# Construct the desired output name
set(OUTPUT_NAME
    "${PROJECT_NAME}.${CURRENT_PLATFORM}.${CURRENT_BUILD_TYPE}.${CURRENT_ARCH}")

# Set the output directory and name for the Library
set_target_properties(
  ${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
                             OUTPUT_NAME ${OUTPUT_NAME})
