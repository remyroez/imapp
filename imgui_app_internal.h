// dear imgui app: standalone application starter kit
// (internal structures/api)

#pragma once
#include "imgui_internal.h"

namespace ImGuiApp
{
    // for Dear ImGui
    IMGUI_APP_API bool SetupImGui();
    IMGUI_APP_API void CleanupImGui();

    // for Platform
    IMGUI_APP_API bool SetupPlatform(const char* name);
    IMGUI_APP_API bool ProcessEventPlatform();
    IMGUI_APP_API bool InitPlatform();
    IMGUI_APP_API void BeginFramePlatform();
    IMGUI_APP_API void EndFramePlatform();
    IMGUI_APP_API void CleanupPlatform();
    IMGUI_APP_API void ShutdownPlatform();
    IMGUI_APP_API bool IsRequestedQuitPlatform();

    // for Renderer
    IMGUI_APP_API bool InitRenderer();
    IMGUI_APP_API void BeginFrameRenderer();
    IMGUI_APP_API void EndFrameRenderer(const ImVec4 &clear_col = ImVec4(0, 0, 0, 1.f));
    IMGUI_APP_API void CleanupRenderer();
}