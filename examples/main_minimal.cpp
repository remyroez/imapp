// dear imgui app: standalone example application
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_app.h"

namespace
{

// Our state (make them static = more or less global) as a convenience to keep the example terse.
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int my_image_width = 0;
int my_image_height = 0;
ImTextureID my_image_texture;
bool loaded_texture = false;

bool once = false;

} // namespace

IMGUI_APP_MAIN("Dear ImGui App minimal example")
{
    // Setup once
    if (!once)
    {
        once = true;

        // Load Texture
        // - We will here use ImGuiApp::LoadTextureFromFile to load images from disk.
#ifndef IMGUI_DISABLE_FILE_FUNCTIONS
        loaded_texture = ImGuiApp::LoadTextureFromFile("MyImage01.jpg", &my_image_texture, &my_image_width, &my_image_height);
#endif
    }

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        if (ImGui::ColorEdit3("clear color", (float*)&clear_color)) // Edit 3 floats representing a color
        {
            ImGuiApp::SetClearColor(clear_color);
        }

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // Ex. Show a loaded texture.
    if (loaded_texture)
    {
        ImGui::SetNextWindowPos(ImVec2(60, 300), ImGuiCond_FirstUseEver);
        ImGui::Begin("Texture Text");
        ImGui::Text("pointer = %p", my_image_texture);
        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image(my_image_texture, ImVec2(my_image_width, my_image_height));
        ImGui::End();
    }
}
