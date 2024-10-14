cmake_minimum_required(VERSION 3.20.0)

project(Common)

# GLOBING FILES
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Logging
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog spdlog_header_only)
target_link_libraries(${PROJECT_NAME} PUBLIC cpptrace::cpptrace)

if(PROFILER_ENABLED)
  message("\n- PROFILE_ENABLED\n")
  target_compile_definitions(${PROJECT_NAME} PUBLIC PROFILER_ENABLED)
  target_link_libraries(Common PUBLIC TracyClient)
else()
  message("\n- PROFILER DISABLED\n")
endif()

if(BUILD_GODOT AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PUBLIC GODOT)
  target_link_libraries(${PROJECT_NAME} PUBLIC godot-cpp)
endif()

if(BUILD_WRAPPER AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PUBLIC UNITY_LOGGER)
endif()

if(BUILD_WRAPPER AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE UNITY_LOGGER)
endif()
