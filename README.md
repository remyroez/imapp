# imapp

Standalone application starter kit for [Dear ImGui](https://github.com/ocornut/imgui)

## Usage

### Basic

```cpp
#include "imgui.h"
#include "imapp.h"

int main(int argc, char *argv[])
{
    if (ImApp::BeginApplication("Example"))
    {
        int my_image_width = 0;
        int my_image_height = 0;
        ImTextureID my_image_texture;
        bool success = ImApp::LoadTextureFromFile("MyImage01.jpg", &my_image_texture, &my_image_width, &my_image_height);

        while (ImApp::BeginFrame())
        {
            if (success)
            {
                ImGui::Begin("Texture");
                ImGui::Image(my_image_texture, ImVec2(my_image_width, my_image_height));
                ImGui::End();
            }
            ImApp::EndFrame();
        }
    }
    ImApp::EndApplication();

    return 0;
}
```

### Minimal

```cpp
#include "imgui.h"
#include "imapp.h"

IMAPP_MAIN("Minimal Example")
{
    ImGui::Text("foo bar baz");
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

### Renderer

- OpenGL 2
- OpenGL 3
- Vulkan ([customized](https://github.com/martty/imgui))

#### OpenGL Loader

- [GLEW](http://glew.sourceforge.net/)
- [GL3W](https://github.com/skaslev/gl3w)
- [GLAD](https://github.com/Dav1dde/glad) (not tested)
- [glbinding](https://github.com/cginternals/glbinding)
    - v2
    - v3 (not tested)

## Links

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SDL2 CMake modules](https://github.com/aminosbh/sdl2-cmake-modules)
- [stb](https://github.com/nothings/stb)
- [martty/imgui](https://github.com/martty/imgui) (User texture binding for Vulkan Renderer)

## License

MIT License
