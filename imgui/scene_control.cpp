#include "imgui/scene_control.h"

#include "imgui/third_party/imgui_impl_glfw.h"
#include "imgui/third_party/imgui_impl_opengl3.h"

#define CAM_POS_RANGE 50

void render_control(Scene& scene)
{
    static float background_color[3] = {scene.background.r, scene.background.g, scene.background.b};

    ImGui::Begin("OpenGL Playground!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Debugging the global scene."); // Display some text (you can use a format strings too)
    // ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
    // ImGui::Checkbox("Another Window", &show_another_window);
    // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("ViewPos_X", &primary_cam.cameraPos.x, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("ViewPos_Y", &primary_cam.cameraPos.y, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("ViewPos_Z", &primary_cam.cameraPos.z, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::SliderFloat("ViewDir_X", &primary_cam.cameraFront.x, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("ViewDir_Y", &primary_cam.cameraFront.y, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("ViewDir_Z", &primary_cam.cameraFront.z, -CAM_POS_RANGE, CAM_POS_RANGE); // Edit 1 float using a slider from 0.0f to 1.0f

    // background_color[0] = scene.background.r;
    // background_color[1] = scene.background.g;
    // background_color[2] = scene.background.b;

    ImGui::ColorEdit3("clear color", (float *)&background_color); // Edit 3 floats representing a color
    scene.background.r = background_color[0];
    scene.background.g = background_color[1];
    scene.background.b = background_color[2];

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
