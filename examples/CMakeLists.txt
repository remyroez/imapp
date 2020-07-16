cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)

# CMake Module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2-cmake-modules)

# Project and Executable
project(imgui_app_example C CXX)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(IMGUI_APP_EXAMPLE_EMSCRIPTEN_SHELL ${IMGUI_EXAMPLE_DIR}/example_emscripten/shell_minimal.html)
    set(IMGUI_APP_EXAMPLE_LINK_FLAGS "-s USE_SDL=2 -s FETCH=1 --shell-file ${IMGUI_IMPL_TEMP_EMSCRIPTEN_SHELL}")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${IMGUI_APP_EXAMPLE_LINK_FLAGS})
    #set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")
endif()

# Dear ImGui
include(cmake/imgui.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES})

# Standalone application starter kit
include(cmake/imgui_app.cmake)
target_link_libraries(${PROJECT_NAME} ${IMGUI_APP_LIBRARIES})

# Example sources

if(EMSCRIPTEN)
    target_sources(${PROJECT_NAME} PRIVATE main_emscripten.cpp)
else()
    target_sources(${PROJECT_NAME} PRIVATE main.cpp)
endif()

