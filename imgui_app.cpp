// dear imgui app: standalone application starter kit

#include "imgui.h"
#include "imgui_app.h"
#include "imgui_app_internal.h"

#ifdef IMGUI_APP_STB_NAMESPACE
namespace IMGUI_APP_STB_NAMESPACE
{
#endif

#define STB_IMAGE_IMPLEMENTATION

#ifdef IMGUI_APP_STB_IMAGE_FILENAME
#include IMGUI_APP_STB_IMAGE_FILENAME
#else
#include "imgui_app_stb_image.h"
#endif

#ifdef IMGUI_APP_STB_NAMESPACE
} // namespace ImStb
using namespace IMGUI_APP_STB_NAMESPACE;
#endif

namespace
{

ImGuiContext *root_context = nullptr;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool done = false;

bool SetupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    root_context = ImGui::CreateContext();

#ifdef IMGUI_APP_SYSTEM_EMSCRIPTEN
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
#endif

    return root_context != nullptr;
}

void CleanupImGui()
{
    ImGui::DestroyContext();
    root_context = nullptr;
}

}

namespace ImGuiApp
{

bool BeginApplication(const char* name)
{
    bool succeeded = false;

    if (!SetupPlatform(name))
    {
        //printf("Error: %s\n", SDL_GetError());
    }
    else if (!SetupRenderer())
    {
        //fprintf(stderr, "Failed to Setup Renderer Bindings!\n");
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

    ShutdownRenderer();
    ShutdownPlatform();
}

bool BeginFrame()
{
    ProcessEventPlatform();

    // Start the Dear ImGui frame
    BeginFrameRenderer();
    BeginFramePlatform();
    ImGui::NewFrame();

    return !done;
}

void EndFrame()
{
    // Rendering
    ImGui::Render();
    EndFrameRenderer(clear_color);
    EndFramePlatform();
}

void RequestQuit()
{
    done = true;
}

void CancelQuit()
{
    done = false;
}

bool IsRequestedQuit()
{
    return done;
}

void SetClearColor(const ImVec4& col)
{
    clear_color = col;
}

bool LoadTextureFromFile(const char* filename, ImTextureID* out_texture_id, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;
    
    bool ret = CreateTexture(image_data, image_width, image_height, out_texture_id);

    stbi_image_free(image_data);

    if (out_width) *out_width = image_width;
    if (out_height) *out_height = image_height;
    
    return ret;
}

bool LoadTextureFromMemory(const unsigned char* data, int size, ImTextureID* out_texture_id, int* out_width, int* out_height)
{
    // Load from memory
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory(data, size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;
    
    bool ret = CreateTexture(image_data, image_width, image_height, out_texture_id);

    stbi_image_free(image_data);

    if (out_width) *out_width = image_width;
    if (out_height) *out_height = image_height;
    
    return ret;
}

}
