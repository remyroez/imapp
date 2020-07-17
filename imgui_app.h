// dear imgui app: standalone application starter kit

#pragma once
#include "imgui.h"      // IMGUI_API

#ifndef IMGUI_APP_API
#define IMGUI_APP_API              IMGUI_API
#endif

// IMGUI_APP_RENDERER_OPENGL
#if defined(IMGUI_APP_RENDERER_OPENGL)
// defined
#elif !defined(IMGUI_APP_RENDERER_OPENGL3) && !defined(IMGUI_APP_RENDERER_OPENGL2)
// not opengl
#else
#define IMGUI_APP_RENDERER_OPENGL
#endif

// IMGUI_APP_SYSTEM_EMSCRIPTEN
#if defined(IMGUI_APP_SYSTEM_EMSCRIPTEN)
// defined
#elif !defined(__EMSCRIPTEN__)
// not emscripten
#else
#define IMGUI_APP_SYSTEM_EMSCRIPTEN
#endif

namespace ImGuiApp
{
    IMGUI_APP_API bool BeginApplication(const char* name);
    IMGUI_APP_API void EndApplication();

    IMGUI_APP_API bool BeginFrame();
    IMGUI_APP_API void EndFrame();

    IMGUI_APP_API void StartMainLoop(void (*func)(void*), void* user_data = NULL);

    IMGUI_APP_API void RequestQuit();
    IMGUI_APP_API void CancelQuit();
    IMGUI_APP_API bool IsRequestedQuit();

    IMGUI_APP_API void SetClearColor(const ImVec4& col);

    IMGUI_APP_API bool LoadTextureFromFile(const char* filename, ImTextureID* out_texture_id, int* out_width, int* out_height);
    IMGUI_APP_API bool LoadTextureFromMemory(const unsigned char* data, int size, ImTextureID* out_texture_id, int* out_width, int* out_height);
}
