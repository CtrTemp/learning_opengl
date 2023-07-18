#include "interaction.h"

Mouse primary_mouse = Mouse();
KeyBoard primary_keyboard = KeyBoard();

// 帧时间计数器，定义为全局的
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

/********************************  窗口回调 ********************************/
// window resize callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/********************************  鼠标回调函数 ********************************/
// 鼠标移动交互回调函数
void Mouse::mouse_moving_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (!isDraging)
    {
        return;
    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    primary_cam.yaw += xoffset;
    primary_cam.pitch -= yoffset;

    if (primary_cam.pitch > 89.0f)
        primary_cam.pitch = 89.0f;
    if (primary_cam.pitch < -89.0f)
        primary_cam.pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(primary_cam.yaw)) * cos(glm::radians(primary_cam.pitch));
    direction.y = sin(glm::radians(primary_cam.pitch));
    direction.z = sin(glm::radians(primary_cam.yaw)) * cos(glm::radians(primary_cam.pitch));
    primary_cam.cameraFront = glm::normalize(direction);
}

// 鼠标点击回调
void Mouse::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        double x;
        double y;
        isDraging = !isDraging;
        if (!isDraging)
        {
            firstMouse = true;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        // do nothing currently
    }
}

// 鼠标滚轮回调
void Mouse::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    primary_cam.fov -= (float)yoffset;
    if (primary_cam.fov < 1.0f)
        primary_cam.fov = 1.0f;
    if (primary_cam.fov > 45.0f)
        primary_cam.fov = 45.0f;
}

// 由于类的成员函数会默认传入一个 this 指针作为参数，所以不能直接被注册为回调函数，故这里嵌套一层
void primary_mouse_moving_call_back(GLFWwindow *window, double xpos, double ypos)
{
    primary_mouse.mouse_moving_callback(window, xpos, ypos);
}

void primary_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    primary_mouse.mouse_button_callback(window, button, action, mods);
}

void primary_mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    primary_mouse.scroll_callback(window, xoffset, yoffset);
}

/********************************  键盘回调函数 ********************************/

void KeyBoard::keyboard_callback(GLFWwindow *window, Camera &cam)
{
    // // middle speed
    // float cameraSpeed = 2.5f * deltaTime;
    // fast speed
    float cameraSpeed = 5.0f * deltaTime;
    // // vary fast speed
    // float cameraSpeed = 15.0f * deltaTime;
    // // hyper fast speed
    // float cameraSpeed = 50.0f * deltaTime;


    // Esc 用于退出绘制
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Tab 用于切换绘制模式（线框/填充）
    static bool polygon_mode_line = true;
    static bool TAB_Press_State = false;
    // 通过变量来控制检测一次按键的按下并抬起操作
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, polygon_mode_line ? GL_LINE : GL_FILL); // render mode
        TAB_Press_State = true;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && TAB_Press_State == true)
    {
        TAB_Press_State = false;
        polygon_mode_line = !polygon_mode_line;
    }

    // EQ 绝对位置运动控制
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam.cameraPos += cameraSpeed * cam.worldUp;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam.cameraPos += cameraSpeed * cam.worldDown;

    // WASD 相对位置运动控制
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.cameraPos += cameraSpeed * cam.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.cameraPos -= cameraSpeed * cam.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.cameraPos -= glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.cameraPos += glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
}
void primary_keyboard_callback(GLFWwindow *window, Camera &cam)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    primary_keyboard.keyboard_callback(window, cam);
}