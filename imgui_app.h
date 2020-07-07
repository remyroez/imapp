// dear imgui app: standalone application starter kit

#pragma once
#include "imgui.h"      // IMGUI_API

#ifndef IMGUI_APP_API
#define IMGUI_APP_API              IMGUI_API
#endif

namespace ImGuiApp
{
    IMGUI_APP_API bool BeginApplication(const char* name);
    IMGUI_APP_API void EndApplication();

    IMGUI_APP_API bool BeginFrame();
    IMGUI_APP_API void EndFrame();

    IMGUI_APP_API void RequestQuit();
    IMGUI_APP_API void CancelQuit();
    IMGUI_APP_API bool IsRequestedQuit();

    IMGUI_APP_API void SetClearColor(const ImVec4& col);
}
