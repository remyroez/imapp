# imgui_app

Standalone application starter kit for [Dear ImGui](https://github.com/ocornut/imgui)

## Usage

```cpp
#include "imgui.h"
#include "imgui_app.h"

int main(int argc, char *argv[])
{
    if (ImGuiApp::BeginApplication("Dear ImGui Standalone application"))
    {
        while (ImGuiApp::BeginFrame())
        {
            // ...
            ImGuiApp::EndFrame();
        }
    }
    ImGuiApp::EndApplication();

    return 0;
}
```

## Supported environments

### System

- Windows (not tested)
- macOS (not tested)
- Linux
    - Ubuntu
    - other distros (not tested)
- Emscripten (WIP)

### Platform

- [SDL2](https://www.libsdl.org/)
- [GLFW](https://github.com/glfw/glfw)

### Renderer

- OpenGL 2
- OpenGL 3
- Vulkan

#### OpenGL Loader

- [GLEW](http://glew.sourceforge.net/)
- [GL3W](https://github.com/skaslev/gl3w) (not tested)
- [GLAD](https://github.com/Dav1dde/glad) (not tested)
- [glbinding](https://github.com/cginternals/glbinding) (not tested)

## Links

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SDL2 CMake modules](https://github.com/aminosbh/sdl2-cmake-modules)

## License

MIT License
