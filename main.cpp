
#include "camera.h"
#include "interaction.h"
#include "scene.h"
#include "render_loop.h"

#include "imgui/third_party/imgui_impl_glfw.h"
#include "imgui/third_party/imgui_impl_opengl3.h"

#include "imgui/scene_control.h"

int main()
{
    // glfw init
    glfwInit();
    // GL 3.0 + GLSL 330
    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // // 指定 MSAA 超采样个数 （使用offline方法的时候请注释掉以下的语句）
    // glfwWindowHint(GLFW_SAMPLES, 4);

    // create window instance
    GLFWwindow *window = glfwCreateWindow(primary_cam.frame_width, primary_cam.frame_height, "OpenGL Playground", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // glad init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 注册键盘交互回调函数
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // （游戏模式下，不显示鼠标的效果）
    glfwSetCursorPosCallback(window, primary_mouse_moving_call_back);  // 注册鼠标移动交互回调函数
    glfwSetScrollCallback(window, primary_mouse_scroll_callback);      // 注册鼠标滚轮交互回调
    glfwSetMouseButtonCallback(window, primary_mouse_button_callback); // 注册鼠标点击交互回调函数


    // // demo 场景生成
    // Scene playground = gen_playground_scene_p1_simple();
    // Scene playground = gen_playground_scene_p2_texture();
    // Scene playground = gen_playground_scene_p3_light_source();
    // Scene playground = gen_playground_scene_p4_normal_mapping();
    Scene playground = gen_playground_scene_p5_height_mapping();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = false; // 这个先不用
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(400, 300)); // 宽400 高300

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            render_control(playground);
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // // demo 场景绘制
        // playground_demo_loop_p1_simple(playground);
        // playground_demo_loop_p2_texture(playground);
        // playground_demo_loop_p3_light_source(playground);
        // playground_demo_loop_p4_normal_mapping(playground);
        playground_demo_loop_p5_height_mapping(playground);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 按键交互
        primary_keyboard_callback(window, primary_cam);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
