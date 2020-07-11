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
        int my_image_width = 0;
        int my_image_height = 0;
        ImTextureID my_image_texture;
        ImGuiApp::LoadTextureFromFile("MyImage01.jpg", &my_image_texture, &my_image_width, &my_image_height);

        while (ImGuiApp::BeginFrame())
        {
            ImGui::Image(my_image_texture, ImVec2(my_image_width, my_image_height));
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
- Vulkan ([customized](https://github.com/martty/imgui))

#### OpenGL Loader

- [GLEW](http://glew.sourceforge.net/)
- [GL3W](https://github.com/skaslev/gl3w) (not tested)
- [GLAD](https://github.com/Dav1dde/glad) (not tested)
- [glbinding](https://github.com/cginternals/glbinding) (not tested)

## Links

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SDL2 CMake modules](https://github.com/aminosbh/sdl2-cmake-modules)
- [stb](https://github.com/nothings/stb)
- [martty/imgui](https://github.com/martty/imgui) (User texture binding for Vulkan Renderer)

## License

MIT License
