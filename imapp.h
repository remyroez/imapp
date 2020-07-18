// imapp: standalone application starter kit

#pragma once
#include "imgui.h"      // IMGUI_API

#ifndef IMAPP_API
#define IMAPP_API              IMGUI_API
#endif

// IMAPP_RENDERER_OPENGL
#if defined(IMAPP_RENDERER_OPENGL)
// defined
#elif !defined(IMAPP_RENDERER_OPENGL3) && !defined(IMAPP_RENDERER_OPENGL2)
// not opengl
#else
#define IMAPP_RENDERER_OPENGL
#endif

// IMAPP_SYSTEM_EMSCRIPTEN
#if defined(IMAPP_SYSTEM_EMSCRIPTEN)
// defined
#elif !defined(__EMSCRIPTEN__)
// not emscripten
#else
#define IMAPP_SYSTEM_EMSCRIPTEN
#endif

namespace ImGuiApp
{
    IMAPP_API bool BeginApplication(const char* name);
    IMAPP_API void EndApplication();

    IMAPP_API bool BeginFrame();
    IMAPP_API void EndFrame();

    IMAPP_API void StartMainLoop(void (*func)(void*), void* user_data = NULL);

    IMAPP_API void RequestQuit();
    IMAPP_API void CancelQuit();
    IMAPP_API bool IsRequestedQuit();

    IMAPP_API void SetClearColor(const ImVec4& col);

    IMAPP_API bool LoadTextureFromFile(const char* filename, ImTextureID* out_texture_id, int* out_width, int* out_height);
    IMAPP_API bool LoadTextureFromMemory(const unsigned char* data, int size, ImTextureID* out_texture_id, int* out_width, int* out_height);
}

#define IMAPP_MAIN_EX(NAME, MAIN_LOOP, USER_DATA) \
int main(int, char**) { \
    if (ImGuiApp::BeginApplication(NAME)) { \
        ImGuiApp::StartMainLoop(MAIN_LOOP, USER_DATA); \
    } \
    ImGuiApp::EndApplication(); \
    return 0; \
}

#define IMAPP_MAIN(NAME) \
void Imapp_MainLoop(void*); \
IMAPP_MAIN_EX(NAME, Imapp_MainLoop, NULL) \
void Imapp_MainLoop(void*)

