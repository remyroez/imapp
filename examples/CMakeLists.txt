cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)

# CMake Module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2-cmake-modules)

# Project and Executable
project(imgui_app_example C CXX)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE)

# Copy example resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MyImage01.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Dear ImGui
include(cmake/imgui.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES})

# Emscripten options
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(IMGUI_APP_EXAMPLE_EMSCRIPTEN_SHELL ${IMGUI_EXAMPLE_DIR}/example_emscripten/shell_minimal.html)
    set(IMGUI_APP_EXAMPLE_PRELOAD_FILE "MyImage01.jpg")
    set(IMGUI_APP_EXAMPLE_LINK_FLAGS "-s USE_SDL=2 -s WASM=1 -s FETCH=1")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " -s ALLOW_MEMORY_GROWTH=1")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " -s ASSERTIONS=1")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " --no-heap-copy --preload-file ${IMGUI_APP_EXAMPLE_PRELOAD_FILE}")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " --preload-file ${IMGUI_INCLUDE_DIR}/misc/fonts@/fonts")
    string(APPEND IMGUI_APP_EXAMPLE_LINK_FLAGS " --shell-file ${IMGUI_APP_EXAMPLE_EMSCRIPTEN_SHELL}")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${IMGUI_APP_EXAMPLE_LINK_FLAGS})
endif()

# Standalone application starter kit
include(cmake/imgui_app.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_LIBRARIES})

# Example sources

if(EMSCRIPTEN)
    target_sources(${PROJECT_NAME} PRIVATE main_emscripten.cpp)
else()
    target_sources(${PROJECT_NAME} PRIVATE main.cpp)
endif()

