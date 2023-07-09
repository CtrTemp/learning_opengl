
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include "iostream"

// // 三角形的三个顶点这里我们直接定义为一个确定的全局变量
// float vertices[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f, 0.5f, 0.0f};

// 借助index buffer来使用四个顶点绘制矩形
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f   // top left
};
unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

// 可以先使用这种方式定义一个 vertex shader，先不写成文件形式
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
                                   "}\0";

// window resize callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Esc Exit
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window instance
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 创建 vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 将 shader source 字符串绑定到 vertexShader 实例
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // 使用命令对该字符串在运行时进行编译

    // 以下对 vertex shader 是否编译成功进行检查，如果错误会输出对应的错误信息
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }

    // 创建 fragment shader，同样使用类似的手段，以字符串的形式定义shader，在运行时编译
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // 对编译结果进行check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }

    // 创建一个 着色器程序，并将刚刚创建的 vertexShader 和 fragmentShader 都绑定到这个程序中
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 对该着色器程序是否创建成功进行检测
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER PROGRAM::COMPILATION_FAILED\n");
    }

    // 创建完成并绑定好后，应有的部分已经被导入了GPU，所以这里我们就可以释放CPU端创建的shaders了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 开始创建三角形
    // VAO这里我没有看懂
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /*
        我们的目的是在GPU上创建一个vertex buffer并将从CPU读取的顶点数据导入到这个GPU上的内存区域，这样当GPU访问这个VertexBuffer进行绘制的时候
    将会非常的快。下面的操作就是在GPU上创建这个 Buffer 并将对应的数据导入到对应的内存区域
    */
    unsigned int VBO;      // Vertex Buffer Object
    glGenBuffers(1, &VBO); // 在GPU上生成 vertex buffer，第一个参数是对应buffer的id
    /*
        这里bind的意思有两层：
        首先一点就是说明，我们的VBO的类型是一个  GL_ARRAY_BUFFER
        第二点就是说明，我们之后对 GL_ARRAY_BUFFER 类型缓冲区的操作的实际对象就是 VBO.
        这也验证了下一步操作为 glBufferData 数据填充操作，虽然没有显式指明VBO，但仍然是对VBO进行的数据填充
    */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 这一步将 CPU 上的数据拷贝到刚刚在 GPU 上创建好的 VBO 上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // GL_STREAM_DRAW: 数据被定义一次，仅会被GPU使用有限的那么几次
    // GL_STATIC_DRAW: 数据被定义一次，且可以多次使用
    // GL_DYNAMIC_DRAW: 数据可以被重复修改，并且会被多次使用

    // EBO的创建与VBO同理，只不过它的基本单元是Element，我们也可以说是三角形面元 triangle primitive
    // 其实就是对 index buffer 的创建，通过指明顶点的序号来复用顶点信息，从而使得我们使用四个顶点就可以创建两个三角形
    unsigned int EBO; // Element Buffer Object
    glGenBuffers(1, &EBO);
    // 注意这里的类型是 GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 参数详解？
    // 参数01：vertex的offset，从哪个顶点起始开始设置其参数
    // 参数02：vertex的size，总共要设置多少个顶点参数
    // 参数03：vertex参数的变量类型，这里在GLSL语言中的vec2、vec3、vec4都默认使用float类型
    // 参数04：输入的vector值是否归一化，比如我们使用的是一个整数类型输入，则将其设置为GL_TRUE，输入的float类型的值必须被限制在-1～1之间，这个参数将被设置为GL_FALSE
    // 参数05：两个顶点参数之间的stride，也就是每个顶点数据单元包含的数据占用多少个bytes。这里我们每个顶点就只包含一个position信息，所以顶点与顶点之间的stride就是一个vec3的间距，即 sizeof(float)*3
    // 参数06：指明顶点的position信息在每个顶点数据包中的offset，因为当前每个顶点的参数信息就只有position，所以这个值就是0
    // 我们搞清楚了参数细节，但对于这个函数具体的作用仍然不明朗！
    // 这一步应该是告诉OpenGL应该如何解析一个顶点的数据信息
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0); // vertex attribute 默认是被禁用的，这里我们开启
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // set clear frame color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 将这个 shaderProgram 作为当前选中的着色器（其实就是激活，让其变为当前将要被使用的）
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // // draw points 0-3 from the currently bound VAO with current in-use shader
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
