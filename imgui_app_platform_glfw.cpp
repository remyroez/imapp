// dear imgui app: standalone application starter kit
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

#include "imgui_app.h"
#include "imgui_internal.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"

#ifdef IMGUI_APP_RENDERER_OPENGL
#include "imgui_app_opengl_loader.h"
#endif

// Include glfw3.h after our OpenGL definitions
#ifdef IMGUI_APP_RENDERER_OPENGL2
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#endif
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace
{

GLFWwindow* window = nullptr;

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

}

namespace ImGuiApp
{

bool SetupPlatform(const char* name)
{
    bool succeeded = false;

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        // Error
    }
    else
    {
#ifdef IMGUI_APP_RENDERER_OPENGL
        // Decide GL+GLSL versions
#if !defined(IMGUI_APP_RENDERER_OPENGL3)
        // not OpenGL 3
#elif __APPLE__
        // GL 3.2 Core + GLSL 150
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
        // GL 3.0 + GLSL 130
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
        // GL Context version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, IMGUI_APP_GL_CONTEXT_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, IMGUI_APP_GL_CONTEXT_MINOR_VERSION);
#endif

        // Create window with graphics context
        window = glfwCreateWindow(1280, 720, name, NULL, NULL);

        if (window == NULL)
        {
            // Error
        }
        else
        {
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1); // Enable vsync

#ifdef IMGUI_APP_RENDERER_OPENGL3
            succeeded = InitOpenGLLoader();
#else
            succeeded = true;
#endif
        }
    }

    return succeeded;
}

void ShutdownPlatform()
{
    glfwDestroyWindow(window);
    window = nullptr;
    
    glfwTerminate();
}

bool InitPlatform()
{
    // Setup Platform bindings
#if defined(IMGUI_APP_RENDERER_OPENGL)
    return ImGui_ImplGlfw_InitForOpenGL(window, true);
#elif defined(IMGUI_APP_RENDERER_VULKAN)
    return ImGui_ImplGlfw_InitForVulkan(window, true);
#endif
}

void CleanupPlatform()
{
    ImGui_ImplGlfw_Shutdown();
}

void BeginFramePlatform()
{
    ImGui_ImplGlfw_NewFrame();
}

void EndFramePlatform()
{
    glfwSwapBuffers(window);
}

bool ProcessEventPlatform()
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    if (glfwWindowShouldClose(window))
    {
        RequestQuit();
    }

    return true;
}

void GetFramebufferSize(int &width, int &height)
{
    glfwGetFramebufferSize(window, &width, &height);
}

void *GetProcAddress(const char* proc_name)
{
    return (void *)glfwGetProcAddress(proc_name);
}

}
