
set(IMGUI_APP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/..)
set(IMGUI_APP_INCLUDE_DIR ${IMGUI_APP_SOURCE_DIR})

# Standalone application starter kit
add_library(imgui_app STATIC)
target_include_directories(imgui_app PUBLIC ${IMGUI_APP_INCLUDE_DIR})

# Platform/Renderer Bindings
include(cmake/imgui_app_platform.cmake)
include(cmake/imgui_app_renderer.cmake)
target_link_libraries(imgui_app ${IMGUI_APP_PLATFORM_LIBRARIES})
target_link_libraries(imgui_app ${IMGUI_APP_RENDERER_LIBRARIES})

# Sources
target_sources(imgui_app PRIVATE
  ${IMGUI_APP_SOURCE_DIR}/imgui_app.cpp
)

# Platform
if(IMGUI_APP_PLATFORM_SDL2)
  # SDL2
  add_definitions(-DIMGUI_APP_PLATFORM_SDL2)
  target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_platform_sdl.cpp)
endif()

# Renderer
if(IMGUI_APP_RENDERER_OPENGL)
  # OpenGL
  add_definitions(-DIMGUI_APP_RENDERER_OPENGL)
  target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_opengl_loader.cpp)

  if(IMGUI_APP_RENDERER_OPENGL3)
    # OpenGL 3
    add_definitions(-DIMGUI_APP_RENDERER_OPENGL3)
    target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_opengl3.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL2)
    # OpenGL 2
    add_definitions(-DIMGUI_APP_RENDERER_OPENGL2)
    #target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_opengl2.cpp)
  endif()
elseif(IMGUI_APP_RENDERER_VULKAN)
  # Vulkan
  add_definitions(-DIMGUI_APP_RENDERER_VULKAN)
  #target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app_renderer_vulkan.cpp)
endif()

set(IMGUI_APP_LIBRARIES imgui_app)
