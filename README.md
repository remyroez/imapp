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

### Platform

- [SDL2](https://www.libsdl.org/)
- [GLFW](https://github.com/glfw/glfw) (WIP)

### Renderer

- OpenGL 2/3
- Vulkan

#### OpenGL Loader

- [GLEW](http://glew.sourceforge.net/)
- [GLAD](https://github.com/Dav1dde/glad) (not tested)

## Links

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SDL2 CMake modules](https://github.com/aminosbh/sdl2-cmake-modules)

## License

MIT License
