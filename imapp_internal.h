// imapp: standalone application starter kit
// (internal structures/api)

#pragma once
#include "imgui_internal.h"

namespace ImApp
{
    // for Platform
    IMAPP_API bool SetupPlatform(const char* name, const ImVec2& size);
    IMAPP_API void ShutdownPlatform();

    IMAPP_API bool InitPlatform();
    IMAPP_API void CleanupPlatform();

    IMAPP_API void BeginFramePlatform();
    IMAPP_API void EndFramePlatform();

    IMAPP_API bool ProcessEventPlatform();

    IMAPP_API void GetFramebufferSize(int &width, int &height);
    IMAPP_API void SetFramebufferSizeCallback(void* callback);

    IMAPP_API void* GetProcAddress(const char* proc_name);

    IMAPP_API const char** GetInstanceExtensions(unsigned int* extensions_count);
    IMAPP_API void ReleaseInstanceExtensions(const char** extensions);

    IMAPP_API int CreateWindowSurface(void* instance, const void* allocator, void* surface);

    // for Renderer
    IMAPP_API bool SetupRenderer();
    IMAPP_API void ShutdownRenderer();

    IMAPP_API bool InitRenderer();
    IMAPP_API void CleanupRenderer();

    IMAPP_API void BeginFrameRenderer();
    IMAPP_API void EndFrameRenderer(const ImVec4 &clear_col = ImVec4(0, 0, 0, 1.f));

    IMAPP_API bool CreateTexture(unsigned char* pixels, int width, int height, ImTextureID* out_texture_id);
    IMAPP_API bool UploadFonts();
}
