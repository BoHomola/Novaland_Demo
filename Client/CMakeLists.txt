cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(NovalandClient)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC enet_static)
target_link_libraries(${PROJECT_NAME} PUBLIC Common)
target_link_libraries(${PROJECT_NAME} PUBLIC NovalandShared)
