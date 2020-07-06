// dear imgui app: standalone application starter kit

#include "imgui_app.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "imgui_app_opengl_loader.h"

#include <SDL.h>

namespace
{

SDL_Window* window = nullptr;
SDL_GLContext gl_context;

bool SetupPlatform(const char* name)
{
    bool succeeded = false;

    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        // Error
    }
    else
    {
        // Decide GL+GLSL versions
#if __APPLE__
        // GL 3.2 Core + GLSL 150
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, IMGUI_APP_GL_CONTEXT_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, IMGUI_APP_GL_CONTEXT_MINOR_VERSION);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

        window_flags = (SDL_WindowFlags)(window_flags | SDL_WINDOW_OPENGL);

        window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

        gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        succeeded = true;
    }

    return succeeded;
}

bool SetupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    auto *rootContext = ImGui::CreateContext();

    return rootContext != nullptr;
}

bool InitPlatform()
{
    // Setup Platform bindings
    return ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
}

bool InitRenderer()
{
    // Setup Renderer bindings
    return ImGui_ImplOpenGL3_Init(IMGUI_APP_GLSL_VERSION);
}

bool done = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

bool ProcessEventPlatform()
{
    bool processed = false;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        processed = ImGui_ImplSDL2_ProcessEvent(&event);
        if (!processed)
        {
            processed = true;
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            {
                done = true;
            }
            else
            {
                processed = false;
            }
        }
    }

    return processed;
}

void BeginFrameRenderer()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void BeginFramePlatform()
{
    ImGui_ImplSDL2_NewFrame(window);
}

void EndFrameRenderer(const ImVec4 &clear_col = ImVec4(0, 0, 0, 1.f))
{
    auto &io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_col.x, clear_col.y, clear_col.z, clear_col.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EndFramePlatform()
{
    SDL_GL_SwapWindow(window);
}

void CleanupRenderer()
{
    ImGui_ImplOpenGL3_Shutdown();
}

void CleanupPlatform()
{
    ImGui_ImplSDL2_Shutdown();
}

void CleanupImGui()
{
    ImGui::DestroyContext();
}

void ShutdownPlatform()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

}

namespace ImGuiApp
{

bool BeginApplication(const char* name)
{
    bool succeeded = false;

    if (!SetupImGui())
    {
        //fprintf(stderr, "Failed to Setup Dear ImGui!\n");
    }
    else if (!SetupPlatform(name))
    {
        //printf("Error: %s\n", SDL_GetError());
    }
    else if (!ImGuiApp::InitOpenGLLoader())
    {
        //fprintf(stderr, "Failed to initialize OpenGL loader!\n");
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
    if (ProcessEventPlatform())
    {
        // processed
    }
    else
    {
        // TODO: User event process func
    }

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

}
