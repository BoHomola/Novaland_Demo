cmake_minimum_required(VERSION 3.20.0)

project(NovalandServer)

# GLOBING FILES
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE TESTS tests/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Novaland)

target_link_libraries(${PROJECT_NAME} PRIVATE Common)
target_link_libraries(${PROJECT_NAME} PRIVATE NovalandShared)
target_link_libraries(${PROJECT_NAME} PRIVATE enet_static)

# JSON
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# #Box2D
target_link_libraries(${PROJECT_NAME} PRIVATE box2d)

get_property(DISABLE_SERVER_GUI GLOBAL PROPERTY DISABLE_SERVER_GUI)

if(NOT DISABLE_SERVER_GUI)
  target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
  target_compile_definitions(${PROJECT_NAME} PRIVATE DISABLE_SERVER_GUI)
endif()

# CLI11
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
