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

    // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
    // you may need to backup/reset/restore current shader using the commented lines below.
    //GLint last_program;
    //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
    //glUseProgram(0);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    //glUseProgram(last_program);
}

void CleanupRenderer()
{
    ImGui_ImplOpenGL2_Shutdown();
}

// Original code: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#Example-for-OpenGL-users
bool CreateTexture(unsigned char* pixels, int width, int height, ImTextureID* out_texture_id)
{
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
#ifdef GL_UNPACK_ROW_LENGTH
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    if (out_texture_id != NULL)
    {
        *out_texture_id = reinterpret_cast<ImTextureID>(image_texture);
    }

    return true;
}

}
