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
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_APP_PLATFORM_INCLIUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_PLATFORM_LIBRARIES})
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_APP_PLATFORM_SOURCES})

# Renderer Bindings
set(IMGUI_APP_RENDERER "OpenGL3" CACHE STRING "Renderer Binding")
set(IMGUI_APP_RENDERER_OPENGL OFF)
set(IMGUI_APP_RENDERER_OPENGL2 OFF)
set(IMGUI_APP_RENDERER_OPENGL3 OFF)
set(IMGUI_APP_RENDERER_VULKAN OFF)

if(IMGUI_APP_RENDERER STREQUAL "OpenGL2")
  set(IMGUI_APP_RENDERER_OPENGL ON)
  set(IMGUI_APP_RENDERER_OPENGL2 ON)
elseif(IMGUI_APP_RENDERER STREQUAL "OpenGL3")
  set(IMGUI_APP_RENDERER_OPENGL ON)
  set(IMGUI_APP_RENDERER_OPENGL3 ON)
elseif(IMGUI_APP_RENDERER STREQUAL "Vulkan")
  set(IMGUI_APP_RENDERER_VULKAN ON)
endif()

if(IMGUI_APP_RENDERER_OPENGL) # OpenGL
  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIRS})
  
  target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
  if(IMGUI_APP_RENDERER_OPENGL2)
    target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_EXAMPLE_DIR}/imgui_impl_opengl2.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL3)
    target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_EXAMPLE_DIR}/imgui_impl_opengl3.cpp)
  endif()
elseif(IMGUI_APP_RENDERER_VULKAN) # Vulkan
  find_package(Vulkan REQUIRED)
  include_directories(${Vulkan_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
  target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_EXAMPLE_DIR}/imgui_impl_vulkan.cpp)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DIMGUI_VULKAN_DEBUG_REPORT)
  endif()
endif()

# OpenGL Loaders
set(IMGUI_APP_OPENGL_LOADER "GLEW" CACHE STRING "OpenGL Loader")
set(IMGUI_APP_OPENGL_LOADER_GLEW OFF)
set(IMGUI_APP_OPENGL_LOADER_GLAD OFF)

if(NOT IMGUI_APP_RENDERER_OPENGL)
  # unnecessary
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLEW")
  set(IMGUI_APP_OPENGL_LOADER_GLEW ON)
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLAD")
  set(IMGUI_APP_OPENGL_LOADER_GLAD ON)
endif()

if(IMGUI_APP_OPENGL_LOADER_GLEW)
  find_package(GLEW REQUIRED)
  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
elseif(IMGUI_APP_OPENGL_LOADER_GLAD)
  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
  target_link_libraries(${PROJECT_NAME} ${GLAD_LIBRARIES})
endif()

# Example sources
set(IMGUI_APP_SOURCES "")

if(IMGUI_APP_PLATFORM_SDL2)
  if(IMGUI_APP_RENDERER_OPENGL3)
    list(APPEND IMGUI_APP_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_opengl3/main.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL2)
    list(APPEND IMGUI_APP_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_opengl2/main.cpp)
  elseif(IMGUI_APP_RENDERER_VULKAN)
    list(APPEND IMGUI_APP_SOURCES ${IMGUI_EXAMPLE_DIR}/example_sdl_vulkan/main.cpp)
  endif()
endif()

target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_APP_SOURCES})
