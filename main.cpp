
#include "camera.h"
#include "interaction.h"
#include "scene.h"
#include "render_loop.h"

int main()
{
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window instance
    GLFWwindow *window = glfwCreateWindow(primary_cam.frame_width, primary_cam.frame_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

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

    // demo 场景生成
    Scene primary_scene = gen_multi_rotating_cube_scene();

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        // 按键交互
        primary_keyboard_callback(window, primary_cam);

        // demo 绘制循环
        multi_rotating_cube_demo_loop(primary_scene);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &primary_scene.VAO);
    glDeleteBuffers(1, &primary_scene.VBO);
    glfwTerminate();

    return 0;
}
