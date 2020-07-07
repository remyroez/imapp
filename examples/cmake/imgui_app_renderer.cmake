
set(IMGUI_APP_RENDERER_INCLUDE_DIR ${IMGUI_EXAMPLE_DIR})

# Renderer Bindings
add_library(imgui_app_renderer STATIC)
target_link_libraries(imgui_app_renderer ${IMGUI_LIBRARIES})
target_include_directories(imgui_app_renderer PUBLIC ${IMGUI_APP_RENDERER_INCLUDE_DIR})

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
  target_link_libraries(imgui_app_renderer ${OPENGL_LIBRARIES})
  target_include_directories(imgui_app_renderer PUBLIC ${OPENGL_INCLUDE_DIRS})

  if(IMGUI_APP_RENDERER_OPENGL2)
    target_sources(imgui_app_renderer PRIVATE ${IMGUI_APP_RENDERER_INCLUDE_DIR}/imgui_impl_opengl2.cpp)
  elseif(IMGUI_APP_RENDERER_OPENGL3)
    target_sources(imgui_app_renderer PRIVATE ${IMGUI_APP_RENDERER_INCLUDE_DIR}/imgui_impl_opengl3.cpp)
  endif()

elseif(IMGUI_APP_RENDERER_VULKAN) # Vulkan
  find_package(Vulkan REQUIRED)
  target_link_libraries(imgui_app_renderer ${Vulkan_LIBRARIES})
  target_include_directories(imgui_app_renderer PUBLIC ${Vulkan_INCLUDE_DIRS})
  target_sources(imgui_app_renderer PRIVATE ${IMGUI_APP_RENDERER_INCLUDE_DIR}/imgui_impl_vulkan.cpp)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(imgui_app_renderer PUBLIC IMGUI_VULKAN_DEBUG_REPORT)
  endif()
endif()

# OpenGL Loaders
set(IMGUI_APP_OPENGL_LOADER "GLEW" CACHE STRING "OpenGL Loader")
set(IMGUI_APP_OPENGL_LOADER_GLEW OFF)
set(IMGUI_APP_OPENGL_LOADER_GLAD OFF)

if(NOT IMGUI_APP_RENDERER_OPENGL3)
  # unnecessary
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLEW")
  set(IMGUI_APP_OPENGL_LOADER_GLEW ON)
elseif(IMGUI_APP_OPENGL_LOADER STREQUAL "GLAD")
  set(IMGUI_APP_OPENGL_LOADER_GLAD ON)
endif()

if(IMGUI_APP_OPENGL_LOADER_GLEW)
  find_package(GLEW REQUIRED)
  target_compile_definitions(imgui_app_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
  target_link_libraries(imgui_app_renderer ${GLEW_LIBRARIES})

elseif(IMGUI_APP_OPENGL_LOADER_GLAD)
  target_compile_definitions(imgui_app_renderer PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
  target_link_libraries(imgui_app_renderer ${GLAD_LIBRARIES})
endif()

set(IMGUI_APP_RENDERER_LIBRARIES imgui_app_renderer)
