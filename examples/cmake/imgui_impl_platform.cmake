
set(IMGUI_IMPL_PLATFORM_INCLUDE_DIR ${IMGUI_EXAMPLE_DIR})
set(IMGUI_IMPL_PLATFORM_SOURCE_DIR ${IMGUI_IMPL_PLATFORM_INCLUDE_DIR})

# Platform Bindings
add_library(imgui_impl_platform STATIC)
target_link_libraries(imgui_impl_platform ${IMGUI_LIBRARIES})
target_include_directories(imgui_impl_platform PUBLIC ${IMGUI_IMPL_PLATFORM_INCLUDE_DIR})

# Platform options
option(IMGUI_IMPL_PLATFORM_SDL2 "Platform for SDL2" OFF)
option(IMGUI_IMPL_PLATFORM_GLFW "Platform for GLFW" OFF)

if(IMGUI_IMPL_PLATFORM_SDL2) # SDL2
  find_package(SDL2 REQUIRED)
  target_link_libraries(imgui_impl_platform ${SDL2_LIBRARIES})
  target_include_directories(imgui_impl_platform PUBLIC ${SDL2_INCLUDE_DIRS})
  target_sources(imgui_impl_platform PRIVATE ${IMGUI_IMPL_PLATFORM_SOURCE_DIR}/imgui_impl_sdl.cpp)

elseif(IMGUI_IMPL_PLATFORM_GLFW) # GLFW
  find_package(glfw3 REQUIRED)
  target_link_libraries(imgui_impl_platform glfw)
  target_sources(imgui_impl_platform PRIVATE ${IMGUI_IMPL_PLATFORM_SOURCE_DIR}/imgui_impl_glfw.cpp)
endif()

set(IMGUI_IMPL_PLATFORM_LIBRARIES imgui_impl_platform)
