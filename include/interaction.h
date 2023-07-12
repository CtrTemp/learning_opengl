#ifndef INTERACTION_H
#define INTERACTION_H

#include "global_include.h"
#include "camera.h" // 由于界面交互会涉及相机操作，所以这里引入相机头文件，主要是需访问其全局变量

class Mouse
{
public:
    Mouse()
    {
        lastX = 0;
        lastY = 0;
        firstMouse = true;
        isDraging = false;
        cursor_speed = 1.0f;
        scroll_speed = 1.0f;
    }
    Mouse(float c_speed, float s_speed) : cursor_speed(c_speed), scroll_speed(s_speed){};

    // 可选注册的鼠标交互回调函数
public:
    void mouse_moving_callback(GLFWwindow *window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

public:
    float lastX;
    float lastY;
    bool firstMouse;
    bool isDraging;
    float cursor_speed;
    float scroll_speed;
};

class KeyBoard
{
public:
    KeyBoard()
    {
        moving_speed = 2.5;
    }
    KeyBoard(float m_speed) : moving_speed(m_speed){};

    // 键盘交互回调函数
public:
    void keyboard_callback(GLFWwindow *window, Camera &cam);

public:
    float moving_speed;
};

extern float deltaTime;
extern float lastFrame;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

extern Mouse primary_mouse;
void primary_mouse_moving_call_back(GLFWwindow *window, double xpos, double ypos);
void primary_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void primary_mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

extern KeyBoard primary_keyboard;
void primary_keyboard_callback(GLFWwindow *window, Camera &cam);

#endif