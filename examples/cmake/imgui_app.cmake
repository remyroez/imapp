
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
target_sources(imgui_app PRIVATE ${IMGUI_APP_SOURCE_DIR}/imgui_app.cpp)

set(IMGUI_APP_LIBRARIES imgui_app)
