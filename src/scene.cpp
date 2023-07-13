#include "scene.h"
#include "camera.h"

// // 单个Cube所需的顶点信息
// float vertices[] = {
//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     -0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

//     -0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     -0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     -0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

//     -0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     -0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     -0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     -0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,

//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,

//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     -0.5f, -0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,

//     -0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
//     0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
//     -0.5f, 0.5f, 0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
//     -0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f};

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

Scene gen_multi_rotating_cube_scene()
{
    Scene scene;

    Shader base_shader = Shader("../shaders/shader_file/v.vert", "../shaders/shader_file/f.frag");
    scene.shader.emplace("base_shader", base_shader);

    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

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
    unsigned int viking_texture = load_textures("../textures/viking_room.png");
    // unsigned int ray_tracing_texture = load_textures("../textures/ray_tracing.png");

    scene.textures.emplace("statue_texture", statue_texture);
    scene.textures.emplace("viking_texture", viking_texture);
    // scene.textures.push_back(ray_tracing_texture);

    // 以下是基本用于测试的变换阵
    // 将 uniform buffer 导入之前一定要先将shader进行选中
    scene.shader["base_shader"].use();
    // 定义并导入坐标变换阵
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); // 逆时针旋转90度
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));                       // 长宽高均缩放至原来的0.5倍
    // 指明向哪一个shader传入这个变换矩阵
    unsigned int transformLoc = glGetUniformLocation(scene.shader["base_shader"].ID, "transform");
    // 将变换矩阵数据从 CPU 端导入到 GPU 端
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); // or with shader class

    return scene;
}

Scene gen_lighting_scene()
{
    Scene scene;


    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 6.0f};
    primary_cam.cameraPos = cameraPos;

    Shader light_shader = Shader("../shaders/shader_file/light_base/light.vert", "../shaders/shader_file/light_base/light.frag");
    Shader obj_shader = Shader("../shaders/shader_file/light_base/obj.vert", "../shaders/shader_file/light_base/obj.frag");
    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("obj_shader", obj_shader);

    scene.VAO.emplace("light_vao", 0);
    scene.VAO.emplace("obj_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    /************************ 绑定场景物体 VAO ************************/
    glGenVertexArrays(1, &scene.VAO["obj_vao"]);
    glBindVertexArray(scene.VAO["obj_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    // 顶点位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 顶点法向量
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    /************************ 绑定场景光源 VAO ************************/

    glGenVertexArrays(1, &scene.VAO["light_vao"]);
    glBindVertexArray(scene.VAO["light_vao"]);

    // glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    // 顶点位置 光源不需要顶点法向量的配置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}
