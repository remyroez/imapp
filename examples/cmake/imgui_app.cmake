
set(IMGUI_APP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/..)
set(IMGUI_APP_INCLUDE_DIR ${IMGUI_APP_SOURCE_DIR})

# Standalone application starter kit
add_library(imgui_app STATIC)
target_include_directories(imgui_app PUBLIC ${IMGUI_APP_INCLUDE_DIR})

# Platform options
set(IMGUI_APP_PLATFORM "SDL2" CACHE STRING "Platform Binding")
set(IMGUI_APP_PLATFORM_SDL2 OFF)
set(IMGUI_APP_PLATFORM_GLFW OFF)

if(IMGUI_APP_PLATFORM STREQUAL "SDL2")
  set(IMGUI_APP_PLATFORM_SDL2 ON)
  set(IMGUI_IMPL_PLATFORM_SDL2 ON)
elseif(IMGUI_APP_PLATFORM STREQUAL "GLFW")
  set(IMGUI_APP_PLATFORM_GLFW ON)
  set(IMGUI_IMPL_PLATFORM_GLFW ON)
endif()

# Platform Bindings
include(cmake/imgui_impl_platform.cmake)
target_link_libraries(imgui_app ${IMGUI_IMPL_PLATFORM_LIBRARIES})

# Renderer options
set(IMGUI_APP_RENDERER "OpenGL3" CACHE STRING "Renderer Binding")
set(IMGUI_APP_RENDERER_OPENGL OFF)
set(IMGUI_APP_RENDERER_OPENGL2 OFF)
set(IMGUI_APP_RENDERER_OPENGL3 OFF)
set(IMGUI_APP_RENDERER_VULKAN OFF)

if(IMGUI_APP_RENDERER STREQUAL "OpenGL2")
  set(IMGUI_APP_RENDERER_OPENGL ON)
  set(IMGUI_APP_RENDERER_OPENGL2 ON)
  set(IMGUI_IMPL_RENDERER_OPENGL2 ON)
elseif(IMGUI_APP_RENDERER STREQUAL "OpenGL3")
  set(IMGUI_APP_RENDERER_OPENGL ON)
  set(IMGUI_APP_RENDERER_OPENGL3 ON)
  set(IMGUI_IMPL_RENDERER_OPENGL3 ON)
elseif(IMGUI_APP_RENDERER STREQUAL "Vulkan")
  set(IMGUI_APP_RENDERER_VULKAN ON)
  set(IMGUI_IMPL_RENDERER_VULKAN ON)
endif()

# OpenGL Loader options
set(IMGUI_APP_OPENGL_LOADER "GLEW" CACHE STRING "OpenGL Loader")

if(NOT IMGUI_APP_RENDERER_OPENGL3)
  # unnecessary
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLEW")
  set(IMGUI_IMPL_OPENGL_LOADER_GLEW ON)
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLAD")
  set(IMGUI_IMPL_OPENGL_LOADER_GLAD ON)
endif()

# Renderer Bindings
include(cmake/imgui_impl_renderer.cmake)
target_link_libraries(imgui_app ${IMGUI_IMPL_RENDERER_LIBRARIES})

# Sources
target_sources(imgui_app PRIVATE
  ${IMGUI_APP_SOURCE_DIR}/imgui_app.cpp
)

# Platform
if(IMGUI_APP_PLATFORM_SDL2)
  # SDL2
  target_compile_definitions(imgui_app PUBLIC IMGUI_APP_PLATFORM_SDL2)
  target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_platform_sdl.cpp)
elseif(IMGUI_APP_PLATFORM_GLFW)
  # GLFW
  target_compile_definitions(imgui_app PUBLIC IMGUI_APP_PLATFORM_GLFW)
  target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_platform_glfw.cpp)
endif()

# Renderer
if(IMGUI_APP_RENDERER_OPENGL)
  # OpenGL
  target_compile_definitions(imgui_app PUBLIC IMGUI_APP_RENDERER_OPENGL)
  target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_opengl_loader.cpp)

  if(IMGUI_APP_RENDERER_OPENGL3)
    # OpenGL 3
    target_compile_definitions(imgui_app PUBLIC IMGUI_APP_RENDERER_OPENGL3)
    target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_opengl3.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL2)
    # OpenGL 2
    target_compile_definitions(imgui_app PUBLIC IMGUI_APP_RENDERER_OPENGL2)
    target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_opengl2.cpp)
  endif()
elseif(IMGUI_APP_RENDERER_VULKAN)
  # Vulkan
  target_compile_definitions(imgui_app PUBLIC IMGUI_APP_RENDERER_VULKAN)
  #target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_vulkan.cpp)
endif()

set(IMGUI_APP_LIBRARIES imgui_app)
