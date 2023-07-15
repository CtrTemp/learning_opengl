#include "scene.h"
#include "camera.h"

// 单个Cube所需的顶点信息
GLfloat vertices[] = {
    // Positions          // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

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

    // 导入纹理
    unsigned int statue_texture = load_textures("../textures/statue.jpg");
    unsigned int viking_texture = load_textures("../textures/viking_room.png");

    scene.textures.emplace("statue_texture", statue_texture);
    scene.textures.emplace("viking_texture", viking_texture);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test
    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_lighting_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 3.0f};
    primary_cam.cameraPos = cameraPos;

    Shader light_shader = Shader("../shaders/shader_file/light_base/light.vert", "../shaders/shader_file/light_base/light.frag");
    Shader obj_shader = Shader("../shaders/shader_file/light_base/obj.vert", "../shaders/shader_file/light_base/obj.frag");
    Shader frame_shader = Shader("../shaders/shader_file/light_base/frame.vert", "../shaders/shader_file/light_base/frame.frag");
    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("frame_shader", frame_shader);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 顶点法向量
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // 顶点纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    // 场景物体材质导入
    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置
    float shininess_item = 32.0f;     // 高光项表现力
    scene.shader["obj_shader"].setFloat("material.shininess", shininess_item);

    // 导入纹理
    unsigned int viking_texture = load_textures("../textures/viking_room.png");
    unsigned int frame_texture = load_textures("../textures/rect.jpeg");

    scene.textures.emplace("viking_texture", viking_texture);
    scene.textures.emplace("frame_texture", frame_texture);

    scene.shader["obj_shader"].setInt("material.diffuse", 0);
    scene.shader["obj_shader"].setInt("material.specular", 1);

    // 光照信息导入，注意这里仍然是对 obj_shader 的编辑

    // scene.shader["obj_shader"].setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
    // scene.shader["obj_shader"].setVec3("light.diffuse", 0.8f, 0.8f, 0.8f); // darken diffuse light a bit
    // scene.shader["obj_shader"].setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // // 平行光源方向设置
    // scene.shader["obj_shader"].setVec3("light.direction", -0.2f, -1.0f, -0.3f);
    // // 点光源设置
    // scene.shader["obj_shader"].setFloat("light.constant", 1.0f);
    // scene.shader["obj_shader"].setFloat("light.linear", 0.09f);
    // scene.shader["obj_shader"].setFloat("light.quadratic", 0.032f);
    // // 束状光源设置（聚光灯呢？往这打～）
    // scene.shader["obj_shader"].setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));      // 硬边缘
    // scene.shader["obj_shader"].setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f))); // 平滑边缘

    // 多光源设置
    // 平行光源
    scene.shader["obj_shader"].setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    scene.shader["obj_shader"].setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    scene.shader["obj_shader"].setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // 点光源
    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};
    // point light 1
    scene.shader["obj_shader"].setVec3("pointLights[0].position", pointLightPositions[0]);
    scene.shader["obj_shader"].setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[0].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[0].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    scene.shader["obj_shader"].setVec3("pointLights[1].position", pointLightPositions[1]);
    scene.shader["obj_shader"].setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[1].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[1].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    scene.shader["obj_shader"].setVec3("pointLights[2].position", pointLightPositions[2]);
    scene.shader["obj_shader"].setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[2].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[2].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    scene.shader["obj_shader"].setVec3("pointLights[3].position", pointLightPositions[3]);
    scene.shader["obj_shader"].setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[3].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[3].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight 作为摄像机附加打光，应该在render loop中进行实时更新
    scene.shader["obj_shader"].setVec3("spotLight.position", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("spotLight.direction", primary_cam.cameraFront);
    scene.shader["obj_shader"].setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    scene.shader["obj_shader"].setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("spotLight.constant", 1.0f);
    scene.shader["obj_shader"].setFloat("spotLight.linear", 0.09f);
    scene.shader["obj_shader"].setFloat("spotLight.quadratic", 0.032f);
    scene.shader["obj_shader"].setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    scene.shader["obj_shader"].setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    /************************ 绑定场景光源 VAO ************************/

    glGenVertexArrays(1, &scene.VAO["light_vao"]);
    glBindVertexArray(scene.VAO["light_vao"]);

    // glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    // 顶点位置 光源不需要顶点法向量的配置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // glDepthFunc(GL_ALWAYS);  // 永远都会通过深度测试，也就是说后被渲染的无论如何都会被保留下来
    // glDepthFunc(GL_NEVER);   // 永远不会通过深度测试，屏幕一片黑，，，
    glDepthFunc(GL_LESS); // default ： 这将丢弃深度值高于或等于当前深度缓冲区的值的片段

    // // stencil test
    // glEnable(GL_STENCIL_TEST); // enable stencil test 如果使能了模板缓冲，必须在绘制循环开始前将其清空

    return scene;
}

Scene gen_load_model_scene()
{
    Scene scene;

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 6.0f};
    primary_cam.cameraPos = cameraPos;

    // model 场景生成
    scene.model_obj = Model("../models/backpack.obj");
    // shader 创建

    Shader obj_shader = Shader("../shaders/shader_file/model_base/model.vert", "../shaders/shader_file/model_base/model.frag");
    Shader light_shader = Shader("../shaders/shader_file/model_base/light.vert", "../shaders/shader_file/model_base/light.frag");
    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("light_shader", light_shader);

    scene.shader["obj_shader"].use();
    // 场景光源设置 多光源设置
    // 平行光源
    scene.shader["obj_shader"].setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    scene.shader["obj_shader"].setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    scene.shader["obj_shader"].setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // 点光源
    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};
    // point light 1
    scene.shader["obj_shader"].setVec3("pointLights[0].position", pointLightPositions[0]);
    scene.shader["obj_shader"].setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[0].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[0].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    scene.shader["obj_shader"].setVec3("pointLights[1].position", pointLightPositions[1]);
    scene.shader["obj_shader"].setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[1].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[1].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    scene.shader["obj_shader"].setVec3("pointLights[2].position", pointLightPositions[2]);
    scene.shader["obj_shader"].setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[2].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[2].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    scene.shader["obj_shader"].setVec3("pointLights[3].position", pointLightPositions[3]);
    scene.shader["obj_shader"].setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    scene.shader["obj_shader"].setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[3].constant", 1.0f);
    scene.shader["obj_shader"].setFloat("pointLights[3].linear", 0.09f);
    scene.shader["obj_shader"].setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight 作为摄像机附加打光，应该在render loop中进行实时更新
    scene.shader["obj_shader"].setVec3("spotLight.position", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("spotLight.direction", primary_cam.cameraFront);
    scene.shader["obj_shader"].setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    scene.shader["obj_shader"].setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    scene.shader["obj_shader"].setFloat("spotLight.constant", 1.0f);
    scene.shader["obj_shader"].setFloat("spotLight.linear", 0.09f);
    scene.shader["obj_shader"].setFloat("spotLight.quadratic", 0.032f);
    scene.shader["obj_shader"].setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    scene.shader["obj_shader"].setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    /************************ 绑定场景光源 VAO ************************/

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

    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑VBO
    glBindVertexArray(0);             // 解绑VAO，防止在其他地方错误配置它

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test
    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}
