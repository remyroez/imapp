cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)

# CMake Module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2-cmake-modules)

# Project and Executable
project(imapp_example C CXX)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE)

# Copy example resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MyImage01.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Dear ImGui
include(cmake/imgui.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES})

# Emscripten options
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(IMAPP_EXAMPLE_EMSCRIPTEN_SHELL ${IMGUI_EXAMPLE_DIR}/example_emscripten/shell_minimal.html)
    set(IMAPP_EXAMPLE_PRELOAD_FILE "MyImage01.jpg")
    set(IMAPP_EXAMPLE_LINK_FLAGS "-s USE_SDL=2 -s WASM=1 -s FETCH=1")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " -s ALLOW_MEMORY_GROWTH=1")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " -s ASSERTIONS=1")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " --no-heap-copy --preload-file ${IMAPP_EXAMPLE_PRELOAD_FILE}")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " --preload-file ${IMGUI_INCLUDE_DIR}/misc/fonts@/fonts")
    string(APPEND IMAPP_EXAMPLE_LINK_FLAGS " --shell-file ${IMAPP_EXAMPLE_EMSCRIPTEN_SHELL}")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${IMAPP_EXAMPLE_LINK_FLAGS})
endif()

# Standalone application starter kit
include(cmake/imapp.cmake)
target_link_libraries(${PROJECT_NAME} ${IMAPP_LIBRARIES})

# Example options
option(IMAPP_EXAMPLE_MINIMAL "Minimal example" OFF)

# Example sources
if(IMAPP_EXAMPLE_MINIMAL)
    target_sources(${PROJECT_NAME} PRIVATE main_minimal.cpp)
elseif(EMSCRIPTEN)
    target_sources(${PROJECT_NAME} PRIVATE main_emscripten.cpp)
else()
    target_sources(${PROJECT_NAME} PRIVATE main.cpp)
endif()

