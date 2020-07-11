cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)

# CMake Module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2-cmake-modules)

# Project and Executable
project(imgui_app_example C CXX)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE)

# Dear ImGui
include(cmake/imgui.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES})

# Standalone application starter kit
include(cmake/imgui_app.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_LIBRARIES})

# Example sources
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
