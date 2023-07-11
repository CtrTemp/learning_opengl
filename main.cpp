
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include "iostream"
#include "math.h"

#include "shaders/shaders.h"
#include "textures/gl_textures.h"

// 顶点对应的归一化纹理坐标
// OpenGL下左下角是[0,0]，右上角是 [1,1]
float textCoord[] = {
    1.0f, 1.0f, // top right
    1.0f, 0.0f, // bottom right
    0.0f, 0.0f, // bottom left
    0.0f, 1.0f, // top left
};

// 将以上纹理的坐标值添加到顶点附加属性，作为顶点参数的一部分
// 顶点
float vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f   // top left
};

// 顶点顺序索引
unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

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

    Shader ourShader("../shaders/shader_file/v.vert", "../shaders/shader_file/f.frag");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据
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

    // 告诉 OpenGL 应该如何解释顶点数据（vertex shader 应该如何解析一个顶点的数据包）
    // 参数01：第几个属性？
    // 参数02：对应的参数有几个数值？（比如顶点位置就有三个分别对应其xyz坐标，2D纹理坐标就只有两个分别是st坐标）
    // 参数03：vertex参数的变量类型，这里在GLSL语言中的vec2、vec3、vec4都默认使用float类型
    // 参数04：输入的vector值是否归一化，比如我们使用的是一个整数类型输入，则将其设置为GL_TRUE，输入的float类型的值必须被限制在-1～1之间，这个参数将被设置为GL_FALSE
    // 参数05：两个顶点参数之间的stride，也就是每个顶点数据单元包含的数据占用多少个bytes。这里我们每个顶点就只包含一个position信息，所以顶点与顶点之间的stride就是一个vec3的间距，即 sizeof(float)*3
    // 参数06：指明顶点的position信息在每个顶点数据包中的offset，因为当前每个顶点的参数信息就只有position，所以这个值就是0
    // 我们搞清楚了参数细节，但对于这个函数具体的作用仍然不明朗！
    // 这一步应该是告诉OpenGL应该如何解析一个顶点的数据信息（设置顶点指针属性）

    // 顶点位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 顶点颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // 顶点纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 导入纹理
    unsigned int statue_texture = load_textures("../textures/statue.jpg");
    unsigned int ray_tracing_texture = load_textures("../textures/ray_tracing.png");
    unsigned int viking_texture = load_textures("../textures/viking_room.png");

    // main render loop
    while (!glfwWindowShouldClose(window))
    {

        // 按键断出
        processInput(window);

        // set clear frame color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 选定shader
        // 将这个 shaderProgram 作为当前选中的着色器（其实就是激活，让其变为当前将要被使用的）
        // 选定图形程序（vertex shader 和 fragment shader 连接而成的管线，其实这里是选择了一个特定的渲染管线）
        // glUseProgram(shaderProgram);
        ourShader.use();
        // 以下使用两种方式从CPU端告知GPU端设置的Uniform Buffer编号
        glUniform1i(glGetUniformLocation(ourShader.ID, "ourTextureFromCPU"), 0); // set it manually
        ourShader.setInt("ourTextureFromCPU_ano", 1);                            // or with shader class

        // 向uniform buffer更新值（这里的值将作为fragment shader 的直接输出）
        // (根据时间更新颜色)
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = sin(timeValue) / 2 + 0.5;
        // 以下在 CPU 端创建一个 uniform buffer 实例
        // 第一个参数指定uniform buffer将传入哪个shader
        // 第二个参数是一个字符串，用于指定 uniform buffer 的具体名称，一定要对应
        GLint vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColorFromCPU");
        // 将uniform buffer中的内容传递到GPU端进行更新
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制时，绑定纹理
        // glBindTexture(GL_TEXTURE_2D, ray_tracing_texture); // 绑定单一纹理

        glActiveTexture(GL_TEXTURE0); // 说明我们以下要配置Texture0了
        glBindTexture(GL_TEXTURE_2D, statue_texture);
        glActiveTexture(GL_TEXTURE1); // 说明我们以下要配置Texture1了
        glBindTexture(GL_TEXTURE_2D, viking_texture);
        // 选定特定的VAO（特定的模型/场景）
        glBindVertexArray(VAO);
        // 执行绘制
        // // draw points 0-3 from the currently bound VAO with current in-use shader
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    GLint nrAttribute;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttribute);
    std::cout << "Max Vertex Attribute = " << nrAttribute << std::endl;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}