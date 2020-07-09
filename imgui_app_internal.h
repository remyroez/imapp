// dear imgui app: standalone application starter kit
// (internal structures/api)

#pragma once
#include "imgui_internal.h"

namespace ImGuiApp
{
    // for Platform
    IMGUI_APP_API bool SetupPlatform(const char* name);
    IMGUI_APP_API void ShutdownPlatform();

    IMGUI_APP_API bool InitPlatform();
    IMGUI_APP_API void CleanupPlatform();

    IMGUI_APP_API void BeginFramePlatform();
    IMGUI_APP_API void EndFramePlatform();

    IMGUI_APP_API bool ProcessEventPlatform();

    IMGUI_APP_API void GetFramebufferSize(int &width, int &height);

    IMGUI_APP_API void *GetProcAddress(const char* proc_name);

    // for Renderer
    IMGUI_APP_API bool InitRenderer();
    IMGUI_APP_API void CleanupRenderer();

    IMGUI_APP_API void BeginFrameRenderer();
    IMGUI_APP_API void EndFrameRenderer(const ImVec4 &clear_col = ImVec4(0, 0, 0, 1.f));

    IMGUI_APP_API bool CreateTexture(unsigned char* pixels, int width, int height, ImTextureID* out_texture_id);
}
