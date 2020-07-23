// imapp: standalone application starter kit

#include "imapp.h"
#include "imapp_internal.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

#include "imapp_opengl_loader.h"

namespace ImApp
{

bool SetupRenderer() { return true; }
void ShutdownRenderer() {}

bool InitRenderer()
{
    // Setup Renderer bindings
    return ImGui_ImplOpenGL3_Init(IMAPP_GLSL_VERSION);
}

void BeginFrameRenderer()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void EndFrameRenderer(const ImVec4 &clear_col)
{
    int display_w, display_h;
    GetFramebufferSize(display_w, display_h);

    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_col.x, clear_col.y, clear_col.z, clear_col.w);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#ifdef IMGUI_HAS_VIEWPORT
    UpdateViewportPlatform();
#endif
}

void CleanupRenderer()
{
    ImGui_ImplOpenGL3_Shutdown();
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

bool UploadFonts()
{
    return true;
}

}
