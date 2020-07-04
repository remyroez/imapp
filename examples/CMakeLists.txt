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

# Platform Bindings
include(cmake/imgui_app_platform.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_PLATFORM_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_APP_PLATFORM_INCLIUDE_DIRS})
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_APP_PLATFORM_SOURCES})

# Renderer Bindings
include(cmake/imgui_app_renderer.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_RENDERER_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_APP_RENDERER_INCLIUDE_DIRS})
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_APP_RENDERER_SOURCES})

# Example sources
set(IMGUI_APP_EXAMPLE_SOURCES "")

if(IMGUI_APP_PLATFORM_SDL2)
  if(IMGUI_APP_RENDERER_OPENGL3)
    list(APPEND IMGUI_APP_EXAMPLE_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_opengl3/main.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL2)
    list(APPEND IMGUI_APP_EXAMPLE_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_opengl2/main.cpp)
  elseif(IMGUI_APP_RENDERER_VULKAN)
    list(APPEND IMGUI_APP_EXAMPLE_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_vulkan/main.cpp)
  endif()
endif()

target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_APP_EXAMPLE_SOURCES})
