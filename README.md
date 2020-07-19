# imapp

Standalone application framework for [Dear ImGui](https://github.com/ocornut/imgui)

## Features

- Dear ImGui like Minimum API (referred to [Dear ImGui examples](https://github.com/ocornut/imgui/tree/master/examples))
- Texture loading API (referred to [Dear ImGui tutorial](https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples))

## Usage

### Basic API

Basic API is used just like any other Dear ImGui functions(Begin***/End*** pair).

```cpp
if (ImApp::BeginApplication("Example")) // Setup
{
    while (ImApp::BeginFrame()) // Process events
    {
        ...
        ImApp::EndFrame(); // Rendering
    }
}
ImApp::EndApplication(); // Shutdown
```

### Texture loading API

Loads a texture and returns its size and ImTextureID.

```cpp
int my_image_width = 0;
int my_image_height = 0;
ImTextureID my_image_texture;
bool ret = ImApp::LoadTextureFromFile("MyImage01.jpg", &my_image_texture, &my_image_width, &my_image_height);
IM_ASSERT(ret);
```

### Minimal Macro

You can use integrated macro instead of main function.

```cpp
#include "imapp.h"

IMAPP_MAIN("Minimal Example") // Setup/Process events/Rendering/Shutdown
{
    ImGui::Text(...);
}
```

## Supported environments

### System

- Windows (not tested)
- macOS (not tested)
- Linux
    - Ubuntu
    - other distros (not tested)
- Emscripten

### Platform

- [SDL2](https://www.libsdl.org/)
- [GLFW](https://github.com/glfw/glfw)

## Renderer

- OpenGL 2
- OpenGL 3
- OpenGL ES 2 (for Emscripten)
- Vulkan ([customized](https://github.com/martty/imgui))

#### OpenGL Loader

- [GLEW](http://glew.sourceforge.net/)
- [GL3W](https://github.com/skaslev/gl3w)
- [GLAD](https://github.com/Dav1dde/glad) (not tested)
- [glbinding](https://github.com/cginternals/glbinding)
    - v2
    - v3 (not tested)

## Building

Note: Consult [imapp-template](https://github.com/remyroez/imapp-template) for build example using CMake.

### Add required files

- Dear ImGui core libraries
- Dear ImGui Platform/Renderer bindings
    - If you use Vulkan, use the file described below.
- imapp core libaries
    - `imapp.cpp`
    - `imapp.h`
    - `imapp_internal.h`
    - `imapp_stb_image.h`
- imapp Platform bindings
    - SDL2
        - `imapp_platform_sdl.cpp`
    - GLFW
        - `imapp_platform_glfw.cpp`
- imapp Renderer bindings
    - OpenGL
        - `imapp_opengl_loader.cpp`
        - `imapp_opengl_loader.h`
        - OpenGL 3
            - `imapp_renderer_opengl3.cpp`
        - OpenGL 2
            - `imapp_renderer_opengl2.cpp`
    - Vulkan
        - `imapp_renderer_vulkan.cpp`
        - `imapp_impl_vulkan.cpp` (Custom binding)
        - `imapp_impl_vulkan.h`

### Add required definitions

- Platform
    - SDL2
        - `IMAPP_PLATFORM_SDL2`
    - GLFW
        - `IMAPP_PLATFORM_GLFW`
- Renderer
    - OpenGL 3
        - `IMAPP_RENDERER_OPENGL3`
    - OpenGL 2
        - `IMAPP_RENDERER_OPENGL2`
    - Vulkan
        - `IMAPP_RENDERER_VULKAN`
- OpenGL Loader (Only OpenGL 3)
    - GLEW
        - `IMGUI_IMPL_OPENGL_LOADER_GLEW`
    - GL3W
        - `IMGUI_IMPL_OPENGL_LOADER_GL3W`
    - GLAD
        - `IMGUI_IMPL_OPENGL_LOADER_GLAD`
    - glbinding v2
        - `IMGUI_IMPL_OPENGL_LOADER_GLBINDING2`
    - glbinding v3
        - `IMGUI_IMPL_OPENGL_LOADER_GLBINDING3`

## TODO

- Setup build/test on GitHub Actions
- Test on Windows/macOS
- Support iOS/Android
- Support other platform/renderer

## Links

- [Dear ImGui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb) (Texture loading API using stb_image.h)
- [martty/imgui](https://github.com/martty/imgui) (User texture binding for Vulkan Renderer)

## License

MIT License
