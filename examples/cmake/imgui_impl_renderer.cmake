
set(IMGUI_IMPL_RENDERER_INCLUDE_DIR ${IMGUI_EXAMPLE_DIR})
set(IMGUI_IMPL_RENDERER_SOURCE_DIR ${IMGUI_IMPL_RENDERER_INCLUDE_DIR})

# Renderer Bindings
add_library(imgui_impl_renderer STATIC)
target_link_libraries(imgui_impl_renderer ${IMGUI_LIBRARIES})
target_include_directories(imgui_impl_renderer PUBLIC ${IMGUI_IMPL_RENDERER_INCLUDE_DIR})

# Renderer options
option(IMGUI_IMPL_RENDERER_OPENGL2 "Renderer for OpenGL2" OFF)
option(IMGUI_IMPL_RENDERER_OPENGL3 "Renderer for OpenGL3" OFF)
option(IMGUI_IMPL_RENDERER_VULKAN "Renderer for Vulkan" OFF)

# OpenGL Loader options
option(IMGUI_IMPL_OPENGL_LOADER_GLEW "OpenGL Loader GLEW" OFF)
option(IMGUI_IMPL_OPENGL_LOADER_GL3W "OpenGL Loader GL3W" OFF)
option(IMGUI_IMPL_OPENGL_LOADER_GLAD "OpenGL Loader GLAD" OFF)

# Renderer
set(IMGUI_IMPL_RENDERER_SOURCE "")

if(IMGUI_IMPL_RENDERER_OPENGL2 OR IMGUI_IMPL_RENDERER_OPENGL3) # OpenGL
  find_package(OpenGL REQUIRED)
  target_link_libraries(imgui_impl_renderer ${OPENGL_LIBRARIES})
  target_include_directories(imgui_impl_renderer PUBLIC ${OPENGL_INCLUDE_DIRS})

  if(IMGUI_IMPL_RENDERER_OPENGL2)
    set(IMGUI_IMPL_RENDERER_SOURCE ${IMGUI_IMPL_RENDERER_SOURCE_DIR}/imgui_impl_opengl2.cpp)
  elseif(IMGUI_IMPL_RENDERER_OPENGL3)
    set(IMGUI_IMPL_RENDERER_SOURCE ${IMGUI_IMPL_RENDERER_SOURCE_DIR}/imgui_impl_opengl3.cpp)
  endif()

elseif(IMGUI_IMPL_RENDERER_VULKAN) # Vulkan
  find_package(Vulkan REQUIRED)
  target_link_libraries(imgui_impl_renderer ${Vulkan_LIBRARIES})
  target_include_directories(imgui_impl_renderer PUBLIC ${Vulkan_INCLUDE_DIRS})
  set(IMGUI_IMPL_RENDERER_SOURCE ${IMGUI_IMPL_RENDERER_SOURCE_DIR}/imgui_impl_vulkan.cpp)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_VULKAN_DEBUG_REPORT)
  endif()
endif()

# OpenGL Loader
if(IMGUI_IMPL_OPENGL_LOADER_GLEW) # GLEW
  find_package(GLEW REQUIRED)
  target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
  target_include_directories(imgui_impl_renderer PUBLIC ${GLEW_INCLUDE_DIRS})
  target_link_libraries(imgui_impl_renderer ${GLEW_LIBRARIES})

elseif(IMGUI_IMPL_OPENGL_LOADER_GL3W) # GL3W
  include(cmake/gl3w.cmake)
  target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)
  target_link_libraries(imgui_impl_renderer ${GL3W_LIBRARIES})

elseif(IMGUI_IMPL_OPENGL_LOADER_GLAD) # GLAD
  #TODO: Setup GLAD
  #target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
  #target_include_directories(imgui_impl_renderer PUBLIC ${GLAD_INCLUDE_DIRS})
  #target_link_libraries(imgui_impl_renderer ${GLAD_LIBRARIES})

elseif(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) # glbinding v2
  find_package(glbinding REQUIRED)
  target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
  target_link_libraries(imgui_impl_renderer glbinding::glbinding)

elseif(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) # glbinding v3
  find_package(glbinding REQUIRED)
  target_compile_definitions(imgui_impl_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
  target_link_libraries(imgui_impl_renderer glbinding::glbinding)
endif()

# Renderer definitions
if(NOT IMGUI_IMPL_RENDERER_CUSTOM_DEFINE OR IMGUI_IMPL_RENDERER_CUSTOM_DEFINE STREQUAL "")
  # nop
else()
  target_compile_definitions(imgui_impl_renderer PUBLIC ${IMGUI_IMPL_RENDERER_CUSTOM_DEFINE})
endif()

# Renderer sources
if(NOT IMGUI_IMPL_RENDERER_VULKAN_CUSTOM_SOURCE OR IMGUI_IMPL_RENDERER_VULKAN_CUSTOM_SOURCE STREQUAL "")
  target_sources(imgui_impl_renderer PRIVATE ${IMGUI_IMPL_RENDERER_SOURCE})
else()
  target_sources(imgui_impl_renderer PRIVATE ${IMGUI_IMPL_RENDERER_VULKAN_CUSTOM_SOURCE})
endif()

set(IMGUI_IMPL_RENDERER_LIBRARIES imgui_impl_renderer)
