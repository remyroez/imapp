
set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)
set(IMGUI_EXAMPLE_DIR ${IMGUI_INCLUDE_DIR}/examples)

add_library(imgui STATIC)

target_sources(imgui PRIVATE
    ${IMGUI_INCLUDE_DIR}/imgui.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_demo.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${IMGUI_EXAMPLE_DIR})

set(IMGUI_LIBRARIES imgui)
