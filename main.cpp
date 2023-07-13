
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

    // // demo 场景生成
    // Scene cube_scene = gen_multi_rotating_cube_scene();
    // Scene light_scene = gen_lighting_scene();

    // model 场景生成
    Shader ourShader = Shader("../shaders/shader_file/model_base/model.vert", "../shaders/shader_file/model_base/model.frag");

    Model ourModel("../models/backpack.obj");

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        // 按键交互
        primary_keyboard_callback(window, primary_cam);

        // // demo 绘制循环
        // multi_rotating_cube_demo_loop(cube_scene);
        // scene_light_demo_loop(light_scene);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        // 定义 MVP 变换阵并导入shader
        glm::mat4 view;
        view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // glDeleteVertexArrays(1, &cube_scene.VAO);
    // glDeleteBuffers(1, &cube_scene.VBO);
    // glDeleteVertexArrays(1, &light_scene.VAO);
    // glDeleteBuffers(1, &light_scene.VBO);
    glfwTerminate();

    return 0;
}
