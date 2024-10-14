cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(NovalandClientFlat)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE NovalandClient)

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

# Construct the desired output name
set(OUTPUT_NAME "${PROJECT_NAME}.${CURRENT_PLATFORM}.${CURRENT_ARCH}")

# Set the output directory and name for the Library
set_target_properties(
  ${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
                             OUTPUT_NAME ${OUTPUT_NAME})

# If the release type is Debug, copy the library with a "__" prefix
if(CMAKE_BUILD_TYPE MATCHES Debug AND ${CURRENT_PLATFORM} MATCHES "linux")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      "${CMAKE_BINARY_DIR}/lib${OUTPUT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}"
      "${CMAKE_BINARY_DIR}/__lib${OUTPUT_NAME}.dev${CMAKE_SHARED_LIBRARY_SUFFIX}"
    COMMENT "Copying and renaming the library for Debug build")
endif()
