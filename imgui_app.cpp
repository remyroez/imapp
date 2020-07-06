// dear imgui app: standalone application starter kit

#include "imgui.h"
#include "imgui_app.h"
#include "imgui_app_internal.h"

namespace
{

ImGuiContext *root_context = nullptr;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

}

namespace ImGuiApp
{

bool SetupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    root_context = ImGui::CreateContext();

    return root_context != nullptr;
}

void CleanupImGui()
{
    ImGui::DestroyContext();
    root_context = nullptr;
}

bool BeginApplication(const char* name)
{
    bool succeeded = false;

    if (!SetupPlatform(name))
    {
        //printf("Error: %s\n", SDL_GetError());
    }
    else if (!SetupImGui())
    {
        //fprintf(stderr, "Failed to Setup Dear ImGui!\n");
    }
    else if (!InitPlatform())
    {
        //fprintf(stderr, "Failed to Setup Platform Bindings!\n");
    }
    else if (!InitRenderer())
    {
        //fprintf(stderr, "Failed to Setup Renderer Bindings!\n");
    }
    else
    {
        succeeded = true;
    }

    return succeeded;
}

void EndApplication()
{
    // Cleanup
    CleanupRenderer();
    CleanupPlatform();
    CleanupImGui();

    ShutdownPlatform();
}

bool BeginFrame()
{
    ProcessEventPlatform();

    // Start the Dear ImGui frame
    BeginFrameRenderer();
    BeginFramePlatform();
    ImGui::NewFrame();

    return !IsRequestedQuitPlatform();
}

void EndFrame()
{
    // Rendering
    ImGui::Render();
    EndFrameRenderer(clear_color);
    EndFramePlatform();
}

void SetClearColor(const ImVec4& col)
{
    clear_color = col;
}

}
