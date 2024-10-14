cmake_minimum_required(VERSION 3.20.0)

project(SerializationFiles)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                         $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} INTERFACE Common)
