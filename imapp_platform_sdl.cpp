// imapp: standalone application starter kit
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

#include "imapp.h"
#include "imapp_internal.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"

#ifdef IMAPP_RENDERER_OPENGL
#include "imapp_opengl_loader.h"
#endif

#if defined(IMAPP_SYSTEM_EMSCRIPTEN)
#include <emscripten.h>
#endif

#include <SDL.h>

#ifdef IMAPP_RENDERER_VULKAN
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#endif

namespace
{

SDL_Window* window = NULL;

#ifdef IMAPP_RENDERER_OPENGL
SDL_GLContext gl_context;
#endif

typedef void (* FramebufferSizeCallback)(void*,int,int);
FramebufferSizeCallback framebuffersize_callback = NULL;

}

namespace ImGuiApp
{

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
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

#if defined(IMAPP_RENDERER_OPENGL)
        window_flags = (SDL_WindowFlags)(window_flags | SDL_WINDOW_OPENGL);

        // Decide GL+GLSL versions
#if !defined(IMAPP_RENDERER_OPENGL3)
        // not OpenGL 3
#elif defined(IMAPP_SYSTEM_EMSCRIPTEN)
        // OpenGL ES 2 + Emscripten
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#elif __APPLE__
        // GL 3.2 Core + GLSL 150
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
        // GL Context version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, IMAPP_GL_CONTEXT_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, IMAPP_GL_CONTEXT_MINOR_VERSION);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#elif defined(IMAPP_RENDERER_VULKAN)
        window_flags = (SDL_WindowFlags)(window_flags | SDL_WINDOW_VULKAN);
#endif

        SDL_DisplayMode current;
        SDL_GetCurrentDisplayMode(0, &current);

        window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

#ifdef IMAPP_RENDERER_OPENGL
        gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync
        succeeded = InitOpenGLLoader();
#else
        succeeded = true;
#endif
    }

    return succeeded;
}

void ShutdownPlatform()
{
#ifdef IMAPP_RENDERER_OPENGL
    SDL_GL_DeleteContext(gl_context);
#endif

    SDL_DestroyWindow(window);
    window = NULL;
    
    SDL_Quit();
}

bool InitPlatform()
{
    // Setup Platform bindings
#if defined(IMAPP_RENDERER_OPENGL)
    return ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
#elif defined(IMAPP_RENDERER_VULKAN)
    return ImGui_ImplSDL2_InitForVulkan(window);
#else
    return false;
#endif
}

void CleanupPlatform()
{
    ImGui_ImplSDL2_Shutdown();
}

void BeginFramePlatform()
{
    ImGui_ImplSDL2_NewFrame(window);
}

void EndFramePlatform()
{
#if defined(IMAPP_RENDERER_OPENGL)
    SDL_GL_SwapWindow(window);
#endif
}

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
            if (event.type == SDL_QUIT)
            {
                processed = true;
                RequestQuit();
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(window))
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    processed = true;
                    RequestQuit();
                }
                else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    if (framebuffersize_callback)
                    {
                        framebuffersize_callback(window, (int)event.window.data1, (int)event.window.data2);
                        processed = true;
                    }
                }
            }
            else
            {
                // none.
            }
        }
    }

    return processed;
}

void GetFramebufferSize(int &width, int &height)
{
    SDL_GetWindowSize(window, &width, &height);
}

void SetFramebufferSizeCallback(void* callback)
{
    framebuffersize_callback = (FramebufferSizeCallback)callback;
}

void *GetProcAddress(const char* proc_name)
{
    return SDL_GL_GetProcAddress(proc_name);
}

const char** GetInstanceExtensions(unsigned int* extensions_count)
{
#ifdef IMAPP_RENDERER_VULKAN
    SDL_Vulkan_GetInstanceExtensions(window, extensions_count, NULL);
    const char** extensions = new const char*[*extensions_count];
    SDL_Vulkan_GetInstanceExtensions(window, extensions_count, extensions);

    return extensions;
#else
    return NULL;
#endif
}

void ReleaseInstanceExtensions(const char** extensions)
{
#ifdef IMAPP_RENDERER_VULKAN
    delete[] extensions;
#endif
}

int CreateWindowSurface(void* instance, const void* allocator, void* surface)
{
#ifdef IMAPP_RENDERER_VULKAN
    VkResult err;
    if (SDL_Vulkan_CreateSurface(window, (VkInstance)instance, (VkSurfaceKHR*)surface) == 0)
    {
        err = VK_NOT_READY;
    }
    else
    {
        err = VK_SUCCESS;
    }
    return err;
#else
    return 0;
#endif
}

}
