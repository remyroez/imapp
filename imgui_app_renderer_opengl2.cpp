// dear imgui app: standalone application starter kit

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_sdl_opengl3/ folder**
// See imgui_impl_sdl.cpp for details.

#include "imgui_app.h"
#include "imgui_app_internal.h"

#include "imgui.h"
#include "imgui_impl_opengl2.h"

#include "imgui_app_opengl_loader.h"

namespace ImGuiApp
{

bool InitRenderer()
{
    // Setup Renderer bindings
    return ImGui_ImplOpenGL2_Init();
}

void BeginFrameRenderer()
{
    ImGui_ImplOpenGL2_NewFrame();
}

void EndFrameRenderer(const ImVec4 &clear_col)
{
    int display_w, display_h;
    GetFramebufferSize(display_w, display_h);

    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_col.x, clear_col.y, clear_col.z, clear_col.w);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void CleanupRenderer()
{
    ImGui_ImplOpenGL2_Shutdown();
}

}
