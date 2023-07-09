
// 首先说明 GLAD 是个什么东西：
/*
    GLAD 是当前最新的用来访问OpenGL规范接口的第三方库。它可以让OpenGL的基础渲染变得十分简单。
    它将基础渲染分为以下几个步骤：
    1、初始化GLAD库，加载所有OpenGL函数指针。
    2、创建着色器并附加到着色器程序。
    3、构建缓冲对象并附加到顶点属性。
    4、使用着色器程序，利用渲染接口将缓冲对象按照指定图元类型渲染出来。
*/
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include "iostream"

// 当用户对窗口大小进行缩放时，调用这个回调函数来修改 viewport 参数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 键盘输入事件检测函数：当 Esc 按下后退出循环
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    // 指明我们使用的版本是 OpenGL 3.3 注意你下载的版本高于3.3是兼容的，但不能低于3.3
    // 当前该电脑上的版本是4.5
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 指明大版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 指明小版本
    // 我们使用 core-profile 模式 而非 immidiate mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 如果是 Mac OS 系统则使用这句话

    // 创建窗口实例
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // 创建窗口上下文？

    // GLAD 帮助初始化（加载） OpenGL 的函数指针
    // glfwGetProcAddress 定义了对应当前操作系统的正确函数指针集合
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 前两个参数定义 window 的左下角，后两个参数定义窗口的宽高
    // 注意OpenGL是以左下角为原点的！而Vulkan是左上角
    // 在最终的归一化空间中，0～width 和 0～height 都会被投影到 -1～1 空间
    glViewport(0, 0, 800, 600);

    // 注册窗口 resize 的回调函数，用于修改 viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 为了测试当前demo是否work，在渲染前将framebuffer直接都填充为单一颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // main render loop
    while (!glfwWindowShouldClose(window)) // 每个循环开始时查看窗口是否已经被关闭，关闭则停止循环
    {
        processInput(window);    // 键盘事件
        glfwSwapBuffers(window); // 将已经渲染好的framebuffer中的内容传送到窗口进行显示
        glfwPollEvents();        // 查看是否在当前循环中有事件被触发，比如键盘输入或其他交互等
    }

    glfwTerminate(); // 结束后使用该函数注销掉渲染过程中窗口所调用的所有资源
    return 0;
}
