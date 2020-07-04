
set(IMGUI_APP_PLATFORM_INCLUDE_DIR ${IMGUI_EXAMPLE_DIR})

# Platform Bindings
add_library(imgui_app_platform STATIC)
target_link_libraries(imgui_app_platform ${IMGUI_LIBRARIES})
target_include_directories(imgui_app_platform PUBLIC ${IMGUI_APP_PLATFORM_INCLUDE_DIR})

set(IMGUI_APP_PLATFORM "SDL2" CACHE STRING "Platform Binding")
set(IMGUI_APP_PLATFORM_SDL2 OFF)

if(IMGUI_APP_PLATFORM STREQUAL "SDL2")
  set(IMGUI_APP_PLATFORM_SDL2 ON)
endif()

if(IMGUI_APP_PLATFORM_SDL2) # SDL2
  find_package(SDL2 REQUIRED)
  target_link_libraries(imgui_app_platform ${SDL2_LIBRARIES})
  target_include_directories(imgui_app_platform PUBLIC ${SDL2_INCLUDE_DIRS})
  target_sources(imgui_app_platform PRIVATE ${IMGUI_EXAMPLE_DIR}/imgui_impl_sdl.cpp)
endif()

set(IMGUI_APP_PLATFORM_LIBRARIES imgui_app_platform)
