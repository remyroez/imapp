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

namespace ImApp
{
    // Application (Main Window)
    // - Setup/Shutdown Platform/Renderer/Dear ImGui Context.
    // - Default window size is 1280x720.
    IMAPP_API bool BeginApplication(const char* name);
    IMAPP_API void EndApplication();

    // Frame
    // - BeginFrame: Handles native window events and returns false when the application terminates.
    // - EndFrame: Render draw list.
    IMAPP_API bool BeginFrame();
    IMAPP_API void EndFrame();

    // Run function in a loop utilizing BeginFrame/EndFrame.
    // Use this for Emscripten.
    IMAPP_API void StartMainLoop(void (*func)(void*), void* user_data = NULL);

    // Quit application (or close main window)
    IMAPP_API void RequestQuit();
    IMAPP_API void CancelQuit();
    IMAPP_API bool IsRequestedQuit();

    // Clear color
    IMAPP_API void SetClearColor(const ImVec4& col);

    // Texture loading
    IMAPP_API bool LoadTextureFromFile(const char* filename, ImTextureID* out_texture_id, int* out_width, int* out_height);
    IMAPP_API bool LoadTextureFromMemory(const unsigned char* data, int size, ImTextureID* out_texture_id, int* out_width, int* out_height);
}

// Main Macro
#define IMAPP_MAIN_EX(NAME, MAIN_LOOP, USER_DATA) \
int main(int, char**) { \
    if (ImApp::BeginApplication(NAME)) { \
        ImApp::StartMainLoop(MAIN_LOOP, USER_DATA); \
    } \
    ImApp::EndApplication(); \
    return 0; \
}

// Minimal Main Macro
#define IMAPP_MAIN(NAME) \
void ImApp_MainLoop(void*); \
IMAPP_MAIN_EX(NAME, ImApp_MainLoop, NULL) \
void ImApp_MainLoop(void*)
