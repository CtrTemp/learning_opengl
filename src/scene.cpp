#include "scene.h"

// 单个Cube所需的顶点信息
GLfloat vertices[] = {
    // Positions          // Normals           // Texture Coords
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // top-left
    // Front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top-left
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
                                                        // Right face
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top-right
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // top-left
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
    // Top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top-right
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // bottom-left
};

Scene gen_multi_rotating_cube_scene()
{
    Scene scene;

    Shader base_shader = Shader("../shaders/shader_file/blend_base/base.vert", "../shaders/shader_file/blend_base/base.frag");
    Shader grass_shader = Shader("../shaders/shader_file/blend_base/base.vert", "../shaders/shader_file/blend_base/grass.frag");
    Shader transparent_shader = Shader("../shaders/shader_file/blend_base/base.vert", "../shaders/shader_file/blend_base/transparent.frag");
    scene.shader.emplace("base_shader", base_shader);
    scene.shader.emplace("grass_shader", grass_shader);
    scene.shader.emplace("transparent_shader", transparent_shader);

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
    unsigned int box_texture = load_textures("../textures/box.png", true);
    unsigned int grass_texture = load_textures("../textures/grass.png", true);

    /*
        如果使用默认的 GL_REPEAT ,则 OpenGL 会对边缘的值和纹理下一个重复的值进行插值，但是由于我们使用了透明值，
    纹理图像的顶部将会与底部边缘的纯色值进行插值。这样的结果是一个半透明的有色边框。可以通过设置 GL_CLAMP_TO_EDGE
    解决这个问题。
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    unsigned int transparent_texture = load_textures("../textures/transparent.png", true);

    scene.textures.emplace("box_texture", box_texture);
    scene.textures.emplace("grass_texture", grass_texture);
    scene.textures.emplace("transparent_texture", transparent_texture);

    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setInt("box_texture", 0);

    scene.shader["grass_shader"].use();
    scene.shader["grass_shader"].setInt("grass_texture", 0);

    scene.shader["transparent_shader"].use();
    scene.shader["transparent_shader"].setInt("transparent_texture", 0);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    glEnable(GL_BLEND); // 使能颜色融合，这样就可以渲染半透明表面
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE); // enable face culling
    // define which is front face? （指定顺/逆时针序表示正面） GL_CCW by default
    // GL_CCW ： 逆时针顶点序表示正面
    // GL_CW ： 顺时针顶点序表示正面
    glFrontFace(GL_CCW);
    // which face should be culled? GL_BACK by default
    // GL_BACK ： 反面剔除
    // GL_FRONT ： 正面剔除
    // GL_FRONT_AND_BACK ： 正反面都要剔除
    glCullFace(GL_BACK);

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
    unsigned int viking_texture = load_textures("../textures/viking_room.png", true);
    unsigned int frame_texture = load_textures("../textures/rect.jpeg", true);

    scene.textures.emplace("viking_texture", viking_texture);
    scene.textures.emplace("frame_texture", frame_texture);

    scene.shader["obj_shader"].setInt("material.diffuse", 0);
    scene.shader["obj_shader"].setInt("material.specular", 1);

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

    // stencil test
    glEnable(GL_STENCIL_TEST); // enable stencil test 如果使能了模板缓冲，必须在绘制循环开始前将其清空
    // 定义何时更新模板函数：
    // 参数1：GL_NOTEQUAL：当现有模板值与新的模板值不相等时进行更新
    // 参数2：ref：更新时，模板值将被更新为什么？
    // 参数3：mask：更新值将会取与mask进行AND位操作后得到的值
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // 更新时的行为：
    // 参数1：GL_KEEP：模板测试不通过时保留原来的模板值
    // 参数2：GL_KEEP：深度测试不通过时保留原来的模板值
    // 参数3：GL_REPLACE：深度测试、模板测试均通过时将 glStencilFunc 中设置的第二参数ref值替换旧的模板值
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    return scene;
}

Scene gen_load_model_scene()
{
    Scene scene;

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 6.0f};
    primary_cam.cameraPos = cameraPos;

    // model 场景生成
    // scene.model_obj.emplace("backpack", Model("../models/backpack/backpack.obj"));
    scene.model_obj.emplace("backpack", Model("../models/gun/Cerberus_LP.FBX"));
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

float quadVertices1[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

Scene gen_framebuffer_scene()
{
    Scene scene;
    Shader base_shader = Shader(
        "../shaders/shader_file/framebuffer_base/base.vert",
        "../shaders/shader_file/framebuffer_base/base.frag");
    Shader frame_shader = Shader(
        "../shaders/shader_file/framebuffer_base/frame.vert",
        "../shaders/shader_file/framebuffer_base/frame.frag");

    scene.shader.emplace("base_shader", base_shader);
    scene.shader.emplace("frame_shader", frame_shader);

    /**************************** Cubes Initialization ****************************/
    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    // Load Textures
    unsigned int box_texture = load_textures("../textures/box.png", true);

    scene.textures.emplace("box_texture", box_texture);

    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setInt("box_texture", 0);

    /**************************** Screen quad Initialization ****************************/
    scene.VAO.emplace("frame_vao", 0);
    scene.VBO.emplace("frame_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["frame_vao"]);
    glBindVertexArray(scene.VAO["frame_vao"]);

    glGenBuffers(1, &scene.VBO["frame_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["frame_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices1), quadVertices1, GL_STATIC_DRAW); // 初始化数据

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    scene.shader["frame_shader"].use();

    // 创建一个 Frame Buffer Objcet
    scene.FBO.emplace("base_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["base_fbo"]);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["base_fbo"]); // 绑定 frame buffer，之后所有的读写缓冲操作都会影响这个 frame buffer

    // 这里要为 frame buffer 添加一个纹理附件，纹理附件不需要填充一个特定的纹理，它的作用是用于承接之后的写入
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 在GPU上创建这个纹理，保证纹理的长宽和屏幕一致即可。 最后的 NULL 表示我们不去填充这个纹理内存数据，这部分要等到渲染阶段进行填充
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, primary_cam.frame_width, primary_cam.frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // 对该纹理的参数进行设置
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 解决边缘纹理采样造成的问题（默认最后一个参数是 GL_REPEAT）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0); // 解绑作为颜色附件的 texture

    scene.textures.emplace("screenTexture", texture);
    scene.shader["frame_shader"].setInt("screenTexture", 0); // 注意要先设置纹理，后加入哈希表

    /**
     *      作为 GL_COLOR_ATTACHMENT0 将纹理附件添加到 frame buffer object 上
     *      注意， frame buffer object 成功创建的必要条件之一就是必须要有添加到他上面的附件，这个附件可以是一个颜色缓冲/模板缓冲/深度缓冲，
     * 下面添加一个颜色缓冲附件。
     *      在之后的渲染循环中，当绑定FBO后，所有的绘制操作/命令都将结果渲染到以下的颜色附件中（也就是你添加到上面的纹理，你是以颜色缓冲附件的
     * 形式添加的纹理）。
     * */
    //
    // 参数01：target：我们所创建的帧缓冲的目标类型
    // 参数02：attachement：要添加的附件类型，GL_COLOR_ATTACHMENT0表示是第0个图像纹理，这里应该还可以设为深度缓冲？
    // 参数03：textarget：希望添加的纹理类型
    // 参数04：texture：添加的纹理实例ID
    // 参数05：level：MipMap的等级，这里暂时设为0（应该表示的是最高等级）
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    /**
     *      创建一个 Render Buffer Objcet
     *      注意，Render Buffer Objcet也是 Frame Buffer Objcet 的一个附件，这样做好处是他存储的是原生的渲染数据，没有作数据优化，
     * 所以 offscreen 渲染后可以直接读取并传送到屏幕，中间不用做数据转换，这使得对RBO的操作十分迅速！
     *      这个RBO对象是Write Only的，所以常常被作为深度/模板缓冲附件被添加。这是因为大多数时候，我们不需要对深度/模板缓冲区进行读取
     * 但仍关心深度测试/模板测试。
     *
     * */
    scene.RBO.emplace("base_rbo", 0);
    glGenRenderbuffers(1, &scene.RBO["base_rbo"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["base_rbo"]); // 绑定 render buffer，之后的渲染操作都会影响到

    /**
     *      在GPU端创建一个Render Buffer Object，
     *  GL_DEPTH24_STENCIL8 应该表示的是我们总共有32位数据宽度来存储深度值和模板值，我们将24位分配给深度值存储，8位分配给模板值存储
     * */
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, primary_cam.frame_width, primary_cam.frame_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // 解绑作为深度/模板附件的 RBO

    // 将 RBO 作为深度/模板缓冲附件绑定到 Frame Buffer Objcet 上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["base_rbo"]);

    // check FBO 是否完备
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    }
    // Other render option
    glEnable(GL_DEPTH_TEST);              // enable depth test
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // FBO 解绑

    /**
     *  经过以上，我们已经创建了一个FBO。并且为其添加了两种附件使其变得完备：
     *  1、一个空的 texture 作为颜色缓冲附件，我们最终在FBO上执行渲染操作后的结果将被写入到这个附件中
     *  2、一个render buffer object作为深度/模板缓冲附件，它使得我们的FBO可以进行深度/模板测试
     * */

    return scene;
}

float skyboxVertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

Scene gen_skybox_scene()
{
    Scene scene;

    // model 导入
    scene.model_obj.emplace("back_pack", Model("../models/backpack.obj"));

    Shader base_shader = Shader("../shaders/shader_file/skybox_base/base.vert", "../shaders/shader_file/skybox_base/base.frag");
    Shader model_shader = Shader("../shaders/shader_file/skybox_base/model.vert", "../shaders/shader_file/skybox_base/model.frag");
    Shader skybox_shader = Shader("../shaders/shader_file/skybox_base/sky.vert", "../shaders/shader_file/skybox_base/sky.frag");

    scene.shader.emplace("base_shader", base_shader);
    scene.shader.emplace("model_shader", model_shader);
    scene.shader.emplace("skybox_shader", skybox_shader);

    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    scene.VAO.emplace("skybox_vao", 0);
    scene.VBO.emplace("skybox_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["skybox_vao"]);
    glBindVertexArray(scene.VAO["skybox_vao"]);

    glGenBuffers(1, &scene.VBO["skybox_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["skybox_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW); // 初始化数据

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // 导入纹理
    // Skybox 纹理
    vector<std::string> faces = {
        "../textures/skybox/left.jpg",
        "../textures/skybox/right.jpg",
        "../textures/skybox/top.jpg",
        "../textures/skybox/bottom.jpg",
        "../textures/skybox/front.jpg",
        "../textures/skybox/back.jpg"};

    unsigned int cubemapTexture = loadCubemap(faces);
    scene.textures.emplace("cubemapTexture", cubemapTexture);

    scene.shader["skybox_shader"].use();
    scene.shader["skybox_shader"].setInt("cubemapTexture", 0);

    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setInt("cubemapTexture", 0);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_geometry_shader_scene()
{

    float points[] = {
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f // bottom-left
    };

    Scene scene;

    Shader house_shader = Shader(
        "../shaders/shader_file/geometry_base/geo.vert",
        "../shaders/shader_file/geometry_base/geo.frag",
        "../shaders/shader_file/geometry_base/house.geom");

    scene.shader.emplace("house_shader", house_shader);

    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); // 初始化数据

    // 点位置
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 点颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return scene;
}

Scene gen_explode_model_scene()
{
    Scene scene;

    // model 模型导入
    scene.model_obj.emplace("backpack", Model("../models/backpack.obj"));

    Shader base_shader = Shader(
        "../shaders/shader_file/geometry_explode/model.vert",
        "../shaders/shader_file/geometry_explode/model.frag",
        "../shaders/shader_file/geometry_explode/explode.geom");

    scene.shader.emplace("base_shader", base_shader);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_visualize_model_normal_scene()
{
    Scene scene;

    // model 模型导入
    scene.model_obj.emplace("backpack", Model("../models/backpack.obj"));

    Shader visual_norm_shader = Shader(
        "../shaders/shader_file/geometry_norm/visual_norm.vert",
        "../shaders/shader_file/geometry_norm/visual_norm.frag",
        "../shaders/shader_file/geometry_norm/visual_norm.geom");

    Shader base_shader = Shader(
        "../shaders/shader_file/geometry_norm/model.vert",
        "../shaders/shader_file/geometry_norm/model.frag");

    scene.shader.emplace("visual_norm_shader", visual_norm_shader);
    scene.shader.emplace("base_shader", base_shader);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

float quadVertices[] = {
    // positions     // colors
    -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
    0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

    -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
    0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
    0.05f, 0.05f, 0.0f, 1.0f, 1.0f};

Scene gen_render_instance_scene()
{
    Scene scene;

    Shader base_shader = Shader("../shaders/shader_file/instance_base/base.vert", "../shaders/shader_file/instance_base/base.frag");
    scene.shader.emplace("base_shader", base_shader);

    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW); // 初始化数据

    // 顶点位置
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 顶点颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_render_instance_scene_opt()
{
    // 由于要绘制100个贴片，所以之类将其偏移量进行填充
    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    Scene scene;

    Shader base_shader = Shader("../shaders/shader_file/instance_base/opt.vert", "../shaders/shader_file/instance_base/opt.frag");
    scene.shader.emplace("base_shader", base_shader);

    scene.VAO.emplace("base_vao", 0);
    scene.VBO.emplace("base_vbo", 0);
    scene.VBO.emplace("instance_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["base_vao"]);
    glBindVertexArray(scene.VAO["base_vao"]);

    glGenBuffers(1, &scene.VBO["instance_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["instance_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW); // 初始化数据

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW); // 初始化数据

    // 顶点位置
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 顶点颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["instance_vbo"]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_mars_simu_scene()
{
    primary_cam.cameraPos = glm::vec3(0.0f, 50.0f, 100.0f);

    Scene scene;

    // model 模型导入
    scene.model_obj.emplace("mars", Model("../models/mars/planet.obj"));
    // model 模型导入
    scene.model_obj.emplace("rock", Model("../models/rock/rock.obj"));

    Shader base_shader = Shader(
        "../shaders/shader_file/instance_planet/base.vert",
        "../shaders/shader_file/instance_planet/base.frag");
    Shader asteroid_shader = Shader(
        "../shaders/shader_file/instance_planet/asteroids.vert",
        "../shaders/shader_file/instance_planet/asteroids.frag");
    scene.shader.emplace("base_shader", base_shader);
    scene.shader.emplace("asteroid_shader", asteroid_shader);

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    unsigned int amount = 5000;
    glm::mat4 *modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
    float radius = 100.0;
    float offset = 25.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    // configure instanced array
    // -------------------------
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < scene.model_obj["rock"].meshes.size(); i++)
    {
        unsigned int VAO = scene.model_obj["rock"].meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_default_MSAA_scene()
{
    primary_cam.cameraPos = glm::vec3(2.0f, 2.0f, 4.0f);
    // // 指定 MSAA 超采样个数 （注意这个必须在窗口创建前进行设置，在这里不行）
    // glfwWindowHint(GLFW_SAMPLES, 4);

    Scene scene;

    Shader base_shader = Shader("../shaders/shader_file/MSAA_base/base.vert", "../shaders/shader_file/MSAA_base/base.frag");
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

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 开启 MSAA
    glEnable(GL_MULTISAMPLE);

    return scene;
}

Scene gen_offscreen_MSAA_scene()
{
    primary_cam.cameraPos = glm::vec3(2.0f, 2.0f, 4.0f);

    Scene scene;

    Shader base_shader = Shader(
        "../shaders/shader_file/MSAA_base/base.vert",
        "../shaders/shader_file/MSAA_base/base.frag");
    scene.shader.emplace("base_shader", base_shader);

    Shader quad_shader = Shader(
        "../shaders/shader_file/MSAA_base/frame.vert",
        "../shaders/shader_file/MSAA_base/frame.frag");
    scene.shader.emplace("quad_shader", quad_shader);

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

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // Screen quad VAO
    scene.VAO.emplace("quad_vao", 0);
    scene.VBO.emplace("quad_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["quad_vao"]);
    glBindVertexArray(scene.VAO["quad_vao"]);

    glGenBuffers(1, &scene.VBO["quad_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["quad_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices1), quadVertices1, GL_STATIC_DRAW); // 初始化数据

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    // configure MSAA framebuffer
    // --------------------------
    // 首先创建 MSAA 对应的 Frame Buffer Object
    scene.FBO.emplace("MSAA_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["MSAA_fbo"]);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["MSAA_fbo"]);

    // 创建空纹理，作为 FBO 的颜色缓冲附件，注意纹理要先配置好，再加入哈希表
    unsigned int textureColorBufferMultiSampled;
    glGenTextures(1, &textureColorBufferMultiSampled);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, primary_cam.frame_width, primary_cam.frame_height, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);

    // 创建RBO，作为 FBO 的深度/模板缓冲附件
    scene.RBO.emplace("MSAA_rbo", 0);
    glGenRenderbuffers(1, &scene.RBO["MSAA_rbo"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["MSAA_rbo"]);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, primary_cam.frame_width, primary_cam.frame_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["MSAA_rbo"]);

    // 检查创建 MSAA 对应的FBO的完备性
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 解绑 MSAA 对应的 FBO

    // configure second post-processing framebuffer
    scene.FBO.emplace("intermediate_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["intermediate_fbo"]);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["intermediate_fbo"]);

    // create a color attachment texture
    unsigned int screenTexture;
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, primary_cam.frame_width, primary_cam.frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0); // we only need a color buffer

    scene.shader["quad_shader"].use();
    scene.textures.emplace("screenTexture", screenTexture); // 这句最后执行
    scene.shader["quad_shader"].setInt("screenTexture", 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return scene;
}

Scene gen_offscreen_MSAA_scene_ano()
{
    primary_cam.cameraPos = glm::vec3(2.0f, 2.0f, 4.0f);

    Scene scene;

    Shader base_shader = Shader(
        "../shaders/shader_file/MSAA_base/base.vert",
        "../shaders/shader_file/MSAA_base/base.frag");
    scene.shader.emplace("base_shader", base_shader);

    Shader quad_shader = Shader(
        "../shaders/shader_file/MSAA_base/frame.vert",
        "../shaders/shader_file/MSAA_base/frame.frag");
    scene.shader.emplace("quad_shader", quad_shader);

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

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // Screen quad VAO
    scene.VAO.emplace("quad_vao", 0);
    scene.VBO.emplace("quad_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["quad_vao"]);
    glBindVertexArray(scene.VAO["quad_vao"]);

    glGenBuffers(1, &scene.VBO["quad_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["quad_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices1), quadVertices1, GL_STATIC_DRAW); // 初始化数据

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    // configure MSAA framebuffer
    // --------------------------
    // 首先创建 MSAA 对应的 Frame Buffer Object
    scene.FBO.emplace("MSAA_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["MSAA_fbo"]);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["MSAA_fbo"]);

    // 创建空纹理，作为 FBO 的颜色缓冲附件，注意纹理要先配置好，再加入哈希表
    unsigned int textureColorBufferMultiSampled;
    glGenTextures(1, &textureColorBufferMultiSampled);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, primary_cam.frame_width, primary_cam.frame_height, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    // 将多重采样纹理以颜色附件的形式附加到帧缓冲上
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);

    // 创建RBO，作为 FBO 的深度/模板缓冲附件
    scene.RBO.emplace("MSAA_rbo", 0);
    glGenRenderbuffers(1, &scene.RBO["MSAA_rbo"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["MSAA_rbo"]);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, primary_cam.frame_width, primary_cam.frame_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // 将 RBO 以深度/模板缓冲的形式添加到 FBO 附件上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["MSAA_rbo"]);

    // 检查创建 MSAA 对应的FBO的完备性
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

    // 将重新绑定到默认窗口的 FBO 上
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 解绑 MSAA 对应的 FBO

    // // configure second post-processing framebuffer
    // scene.FBO.emplace("intermediate_fbo", 0);
    // glGenFramebuffers(1, &scene.FBO["intermediate_fbo"]);
    // glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["intermediate_fbo"]);

    // create a color attachment texture
    unsigned int screenTexture;
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, primary_cam.frame_width, primary_cam.frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0); // we only need a color buffer

    scene.shader["quad_shader"].use();
    scene.textures.emplace("screenTexture", screenTexture); // 这句最后执行
    scene.shader["quad_shader"].setInt("screenTexture", 0);

    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //     cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << endl;
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    return scene;
}

float planeVertices[] = {
    // positions            // normals         // texcoords
    10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
    -10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,

    10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
    -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
    10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f};

Scene gen_test_Blinn_Phong_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 3.0f};
    primary_cam.cameraPos = cameraPos;

    Shader obj_shader = Shader(
        "../shaders/shader_file/blinn_phong_base/base.vert",
        "../shaders/shader_file/blinn_phong_base/base.frag");

    scene.shader.emplace("obj_shader", obj_shader);

    scene.VAO.emplace("obj_vao", 0);
    scene.VBO.emplace("base_vbo", 0);

    /************************ 绑定场景物体 VAO ************************/
    glGenVertexArrays(1, &scene.VAO["obj_vao"]);
    glBindVertexArray(scene.VAO["obj_vao"]);

    glGenBuffers(1, &scene.VBO["base_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["base_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW); // 初始化数据

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
    unsigned int floor_texture = load_textures("../textures/floor.jpg", true);

    scene.textures.emplace("floor_texture", floor_texture);

    scene.shader["obj_shader"].setInt("material.diffuse", 0);
    scene.shader["obj_shader"].setInt("material.specular", 1);

    // 多光源设置
    // 平行光源
    scene.shader["obj_shader"].setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    scene.shader["obj_shader"].setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    scene.shader["obj_shader"].setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    scene.shader["obj_shader"].setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // 点光源
    // std::vector<glm::vec3> pointLightPositions = {
    //     glm::vec3(0.7f, 0.2f, 2.0f),
    //     glm::vec3(2.3f, -3.3f, -4.0f),
    //     glm::vec3(-4.0f, 2.0f, -12.0f),
    //     glm::vec3(0.0f, 0.0f, -3.0f)};

    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3(4.0f, 1.0f, 4.0f),
        glm::vec3(4.0f, 2.0f, -4.0f),
        glm::vec3(-4.0f, 3.0f, 4.0f),
        glm::vec3(-4.0f, 4.0f, -4.0f)};
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

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

float planeVertices1[] = {
    // positions            // normals         // texcoords
    25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
    -25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,

    25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
    -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
    25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f};

Scene gen_shadow_mapping_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 5.0f, 10.0f};
    primary_cam.cameraPos = cameraPos;
    // glm::vec3 cameraDir = {-1.0, -1.0, -1.0};
    // primary_cam.cameraFront = cameraDir;

    Shader plane_shader = Shader(
        "../shaders/shader_file/shadow_base/plane.vert",
        "../shaders/shader_file/shadow_base/plane.frag");

    Shader cube_shader = Shader(
        "../shaders/shader_file/shadow_base/cube.vert",
        "../shaders/shader_file/shadow_base/cube.frag");

    Shader depth_shader = Shader(
        "../shaders/shader_file/shadow_base/depth.vert",
        "../shaders/shader_file/shadow_base/depth.frag");

    Shader quad_shader = Shader(
        "../shaders/shader_file/shadow_base/quad.vert",
        "../shaders/shader_file/shadow_base/quad.frag");

    scene.shader.emplace("plane_shader", plane_shader);
    scene.shader.emplace("cube_shader", cube_shader);
    scene.shader.emplace("depth_shader", depth_shader);
    scene.shader.emplace("quad_shader", quad_shader);

    glm::vec3 dirLight_direction = {-1.2f, -1.0f, -0.5f};
    glm::vec3 dirLight_ambient = {0.05f, 0.05f, 0.05f};
    glm::vec3 dirLight_diffuse = {0.4f, 0.4f, 0.4f};
    glm::vec3 dirLight_specular = {0.5f, 0.5f, 0.5f};

    /************************ Plane VAO ************************/

    scene.VAO.emplace("plane_vao", 0);
    scene.VBO.emplace("plane_vbo", 0);
    glGenVertexArrays(1, &scene.VAO["plane_vao"]);
    glBindVertexArray(scene.VAO["plane_vao"]);

    glGenBuffers(1, &scene.VBO["plane_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["plane_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices1), planeVertices1, GL_STATIC_DRAW); // 初始化数据

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
    scene.shader["plane_shader"].use(); // 以下对 obj shader 进行配置
    float shininess_item = 32.0f;       // 高光项表现力
    scene.shader["plane_shader"].setFloat("material.shininess", shininess_item);

    // 导入纹理
    unsigned int floor_texture = load_textures("../textures/floor.jpg", true);

    scene.textures.emplace("floor_texture", floor_texture);

    scene.shader["plane_shader"].setInt("material.diffuse", 0);
    scene.shader["plane_shader"].setInt("material.specular", 1);

    // 平行光源
    scene.shader["plane_shader"].setVec3("dirLight.direction", dirLight_direction);
    scene.shader["plane_shader"].setVec3("dirLight.ambient", dirLight_ambient);
    scene.shader["plane_shader"].setVec3("dirLight.diffuse", dirLight_diffuse);
    scene.shader["plane_shader"].setVec3("dirLight.specular", dirLight_specular);

    glBindVertexArray(0); // 解绑VAO

    /************************ Cube VAO ************************/

    scene.VAO.emplace("cube_vao", 0);
    scene.VBO.emplace("cube_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["cube_vao"]);
    glBindVertexArray(scene.VAO["cube_vao"]);

    glGenBuffers(1, &scene.VBO["cube_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["cube_vbo"]);
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
    scene.shader["cube_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["cube_shader"].setFloat("material.shininess", shininess_item);

    // 导入纹理
    unsigned int cube_texture = load_textures("../textures/floor.jpg", true);

    scene.textures.emplace("floor_texture", cube_texture);

    scene.shader["cube_shader"].setInt("material.diffuse", 0);
    scene.shader["cube_shader"].setInt("material.specular", 1);

    // 平行光源
    scene.shader["plane_shader"].setVec3("dirLight.direction", dirLight_direction);
    scene.shader["plane_shader"].setVec3("dirLight.ambient", dirLight_ambient);
    scene.shader["plane_shader"].setVec3("dirLight.diffuse", dirLight_diffuse);
    scene.shader["plane_shader"].setVec3("dirLight.specular", dirLight_specular);

    glBindVertexArray(0); // 解绑VAO

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    /************************ Depth Map ************************/

    // 创建深度图相关的 Frame Buffer Object
    scene.FBO.emplace("depth_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["depth_fbo"]);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    // 创建深度图的纹理
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    scene.shader["quad_shader"].use();
    scene.textures.emplace("depthMap", depthMap);
    scene.shader["quad_shader"].setInt("depthMap", 0);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]); // 绑定 FBO
    // 刚刚创建的深度图纹理作为深度缓冲附件
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 还原到窗口默认的附件

    return scene;
}

Scene switch_gen_shadow_mapping_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 5.0f, 10.0f};
    primary_cam.cameraPos = cameraPos;

    Shader depth_shader = Shader(
        "../shaders/shader_file/shadow_base/depth.vert",
        "../shaders/shader_file/shadow_base/depth.frag");

    Shader quad_shader = Shader(
        "../shaders/shader_file/shadow_base/quad.vert",
        "../shaders/shader_file/shadow_base/quad.frag");

    scene.shader.emplace("depth_shader", depth_shader);
    scene.shader.emplace("quad_shader", quad_shader);

    /************************ Plane Vao ************************/
    scene.VAO.emplace("plane_vao", 0);
    glGenVertexArrays(1, &scene.VAO["plane_vao"]);
    glBindVertexArray(scene.VAO["plane_vao"]);

    scene.VBO.emplace("plane_vbo", 0);
    glGenBuffers(1, &scene.VBO["plane_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["plane_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices1), planeVertices1, GL_STATIC_DRAW);
    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    // texCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glBindVertexArray(0); // 解绑 VAO

    unsigned int woodTexture = load_textures("../textures/floor.jpg", true);

    /************************ Depth Map ************************/

    // 创建深度图相关的 Frame Buffer Object
    scene.FBO.emplace("depth_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["depth_fbo"]);

    const unsigned int SHADOW_WIDTH = 1600, SHADOW_HEIGHT = 900; // 这个是深度图的分辨率

    // 创建深度图的纹理
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    // 创建的纹理将作为一个深度缓冲附件被传入
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    scene.shader["quad_shader"].use();
    scene.textures.emplace("depthMap", depthMap);
    scene.shader["quad_shader"].setInt("depthMap", 0);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]); // 绑定 FBO
    // 刚刚创建的深度图纹理作为深度缓冲附件
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    /**
     *  注意，对于这个 FBO 我们没有为其添加颜色附件，这会导致其不完备从而在后面的查验中报错（但实际上好像并不会）
     * 于是我们使用以下的两个语句告诉 OpenGL 我们创建的这个 FBO 并不需要对其进行绘制以及读取颜色缓冲区附件。
     * */
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // 检查创建 MSAA 对应的FBO的完备性
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 还原到窗口默认的附件

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene switch_gen_shadow_mapping_scene_phase2()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 5.0f, 10.0f};
    primary_cam.cameraPos = cameraPos;
    // glm::vec3 cameraDir = {-1.0, -1.0, -1.0};
    // primary_cam.cameraFront = cameraDir;

    Shader obj_shader = Shader(
        "../shaders/shader_file/shadow_base/phase02/obj.vert",
        "../shaders/shader_file/shadow_base/phase02/obj.frag");

    Shader depth_shader = Shader(
        "../shaders/shader_file/shadow_base/phase02/depth.vert",
        "../shaders/shader_file/shadow_base/phase02/depth.frag");


    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("depth_shader", depth_shader);

    /************************ Plane Vao ************************/
    scene.VAO.emplace("plane_vao", 0);
    glGenVertexArrays(1, &scene.VAO["plane_vao"]);
    glBindVertexArray(scene.VAO["plane_vao"]);

    scene.VBO.emplace("plane_vbo", 0);
    glGenBuffers(1, &scene.VBO["plane_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["plane_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices1), planeVertices1, GL_STATIC_DRAW);
    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    // texCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glBindVertexArray(0); // 解绑 VAO


    /************************ Load Texture ************************/
    unsigned int woodTexture = load_textures("../textures/floor.jpg", true);
    scene.textures.emplace("woodTexture", woodTexture);

    /************************ Depth Map ************************/

    // 创建深度图相关的 Frame Buffer Object

    // configure depth map FBO
    // -----------------------
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    scene.FBO.emplace("depth_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["depth_fbo"]);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 版本04：优化：
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    scene.textures.emplace("depthMap", depthMap);

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setInt("diffuseTexture", 0);
    scene.shader["obj_shader"].setInt("depthMap", 1);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_point_light_shadow_mapping_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 0.0f};
    primary_cam.cameraPos = cameraPos;

    Shader obj_shader = Shader(
        "../shaders/shader_file/shadow_base/point_light/obj.vert",
        "../shaders/shader_file/shadow_base/point_light/obj.frag");

    Shader light_shader = Shader(
        "../shaders/shader_file/shadow_base/point_light/light.vert",
        "../shaders/shader_file/shadow_base/point_light/light.frag");

    Shader depth_shader = Shader(
        "../shaders/shader_file/shadow_base/point_light/depth.vert",
        "../shaders/shader_file/shadow_base/point_light/depth.frag",
        "../shaders/shader_file/shadow_base/point_light/depth.geom");

    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("depth_shader", depth_shader);

    /************************ Depth Map ************************/

    // 创建深度图相关的 Frame Buffer Object

    // configure depth map FBO
    // -----------------------

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    scene.FBO.emplace("depth_fbo", 0);
    glGenFramebuffers(1, &scene.FBO["depth_fbo"]);
    // 创建深度图，但注意由于这次是点光源，所以我们应该创建一个立方体深度图 Cube Depth Map
    unsigned int depthCubemap;
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    scene.textures.emplace("depthCubemap", depthCubemap);

    for (unsigned int i = 0; i < 6; ++i)
    {
        // 注意这里在GPU上创建了6张深度图
        // GL_TEXTURE_CUBE_MAP_POSITIVE_X + i 对应了立方体的六个面
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // 绑定到 depth buffer 的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]);
    // CubeMap 纹理将作为深度缓冲区组件被添加到 depth buffer 的 FBO 中
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, scene.textures["depthCubemap"], 0);
    // 声明当前的 FBO 不需要颜色附件
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // 绑定回屏幕默认的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 加载纹理
    unsigned int diffuseTexture = load_textures("../textures/floor.jpg", true);
    scene.textures.emplace("diffuseTexture", diffuseTexture);

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setInt("diffuseTexture", 0);
    scene.shader["obj_shader"].setInt("depthMap", 1);

    // // depth test
    // glEnable(GL_DEPTH_TEST); // enable depth test
    // // Other render option
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

float planeVertices_normal[] = {
    // positions            // normals         // texcoords
    2.0f, 2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,
    -2.0f, 2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -2.0f, -2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,

    2.0f, 2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,
    -2.0f, -2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,
    2.0f, -2.0f, -0.5f, 0.0f, 1.0f, 0.0f, 2.0f, 2.0f};

Scene gen_simple_normal_mapping_scene()
{

    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 3.0f};
    primary_cam.cameraPos = cameraPos;

    Shader obj_shader = Shader(
        "../shaders/shader_file/normal_map_base/base.vert",
        "../shaders/shader_file/normal_map_base/base.frag");

    Shader light_shader = Shader(
        "../shaders/shader_file/normal_map_base/light.vert",
        "../shaders/shader_file/normal_map_base/light.frag");

    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("light_shader", light_shader);

    // 导入纹理
    unsigned int diffuseMap = load_textures("../textures/brickwall.jpg", true);
    unsigned int normalMap = load_textures("../textures/brickwall_normal.jpg", true);

    scene.textures.emplace("diffuseMap", diffuseMap);
    scene.textures.emplace("normalMap", normalMap);

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setInt("diffuseMap", 0);
    scene.shader["obj_shader"].setInt("normalMap", 1);

    glBindVertexArray(0); // 解绑VAO，防止在其他地方错误配置它

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_PBR_light_base_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/base/pbr.vert",
        "../shaders/shader_file/PBR/base/pbr.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setVec3("albedo", 0.5f, 0.0f, 0.0f);
    scene.shader["pbr_shader"].setFloat("ao", 1.0f);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_PBR_light_textured_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/textured_base/pbr.vert",
        "../shaders/shader_file/PBR/textured_base/pbr.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setInt("albedoMap", 0);
    scene.shader["pbr_shader"].setInt("normalMap", 1);
    scene.shader["pbr_shader"].setInt("metallicMap", 2);
    scene.shader["pbr_shader"].setInt("roughnessMap", 3);
    scene.shader["pbr_shader"].setInt("aoMap", 4);

    unsigned int albedo = load_textures("../textures/PBR/mental_ball/rustediron2_basecolor.png", true);
    unsigned int normal = load_textures("../textures/PBR/mental_ball/rustediron2_normal.png", true);
    unsigned int metallic = load_textures("../textures/PBR/mental_ball/rustediron2_metallic.png", true);
    unsigned int roughness = load_textures("../textures/PBR/mental_ball/rustediron2_roughness.png", true);
    unsigned int ao = load_textures("../textures/PBR/mental_ball/rustediron2_normal.png", true);

    scene.textures.emplace("albedoMap", albedo);
    scene.textures.emplace("normalMap", normal);
    scene.textures.emplace("metallicMap", metallic);
    scene.textures.emplace("roughnessMap", roughness);
    scene.textures.emplace("aoMap", ao);
    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_PBR_IBL_diffuse_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/pbr.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/pbr.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/rect_to_cube.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/background.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setVec3("albedo", 0.5f, 0.0f, 0.0f);
    scene.shader["pbr_shader"].setFloat("ao", 1.0f);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Init FBO *********************************/

    scene.VAO.emplace("skybox_vao", 0);
    scene.VBO.emplace("skybox_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["skybox_vao"]);
    glBindVertexArray(scene.VAO["skybox_vao"]);

    glGenBuffers(1, &scene.VBO["skybox_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["skybox_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    /********************************* Load Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/PBR/HDR/sea.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

Scene gen_PBR_IBL_diffuse_scene_p2()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // set depth function to less than AND equal for skybox depth trick.

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/p2/pbr.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/p2/pbr.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/p2/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/p2/rect_to_cube.frag");

    Shader irradiance_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/p2/irradiance.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/p2/irradiance.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/p2/background.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/p2/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("irradiance_shader", irradiance_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setInt("irradianceMap", 0);
    scene.shader["pbr_shader"].setVec3("albedo", 0.5f, 0.0f, 0.0f);
    scene.shader["pbr_shader"].setFloat("ao", 1.0f);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Load Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/HDR/room.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 16, 16, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 16, 16);

    scene.textures.emplace("irradianceMap", irradianceMap);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    scene.shader["irradiance_shader"].use();
    scene.shader["irradiance_shader"].setInt("environmentMap", 0);
    scene.shader["irradiance_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);

    glViewport(0, 0, 16, 16); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["irradiance_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

Scene gen_PBR_IBL_diffuse_scene_ano()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/pbr.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/pbr.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/rect_to_cube.frag");

    Shader irradiance_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/irradiance.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/irradiance.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/background.vert",
        "../shaders/shader_file/PBR/IBL_diffuse/mental_ball/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setInt("irradianceMap", 0);
    // scene.shader["pbr_shader"].setVec3("albedo", 0.5f, 0.0f, 0.0f);
    // scene.shader["pbr_shader"].setFloat("ao", 1.0f);

    scene.shader["pbr_shader"].setInt("albedoMap", 0);
    scene.shader["pbr_shader"].setInt("normalMap", 1);
    scene.shader["pbr_shader"].setInt("metallicMap", 2);
    scene.shader["pbr_shader"].setInt("roughnessMap", 3);
    scene.shader["pbr_shader"].setInt("aoMap", 4);

    unsigned int albedo = load_textures("../textures/PBR/mental_ball/rustediron2_basecolor.png", true);
    unsigned int normal = load_textures("../textures/PBR/mental_ball/rustediron2_normal.png", true);
    unsigned int metallic = load_textures("../textures/PBR/mental_ball/rustediron2_metallic.png", true);
    unsigned int roughness = load_textures("../textures/PBR/mental_ball/rustediron2_roughness.png", true);
    unsigned int ao = load_textures("../textures/PBR/mental_ball/rustediron2_normal.png", true);

    scene.textures.emplace("albedoMap", albedo);
    scene.textures.emplace("normalMap", normal);
    scene.textures.emplace("metallicMap", metallic);
    scene.textures.emplace("roughnessMap", roughness);
    scene.textures.emplace("aoMap", ao);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Init FBO *********************************/

    scene.VAO.emplace("skybox_vao", 0);
    scene.VBO.emplace("skybox_vbo", 0);

    glGenVertexArrays(1, &scene.VAO["skybox_vao"]);
    glBindVertexArray(scene.VAO["skybox_vao"]);

    glGenBuffers(1, &scene.VBO["skybox_vbo"]);
    glBindBuffer(GL_ARRAY_BUFFER, scene.VBO["skybox_vbo"]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 初始化数据

    /********************************* Load Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/PBR/HDR/sea.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    scene.textures.emplace("irradianceMap", irradianceMap);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    scene.shader["irradiance_shader"].use();
    scene.shader["irradiance_shader"].setInt("environmentMap", 0);
    scene.shader["irradiance_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["irradiance_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

Scene gen_PBR_IBL_specular_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/pbr.vert",
        "../shaders/shader_file/PBR/IBL_specular/pbr.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_specular/rect_to_cube.frag");

    Shader irradiance_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/irradiance.vert",
        "../shaders/shader_file/PBR/IBL_specular/irradiance.frag");

    Shader pre_filter_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/filter.vert",
        "../shaders/shader_file/PBR/IBL_specular/filter.frag");

    Shader brdf_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/brdf.vert",
        "../shaders/shader_file/PBR/IBL_specular/brdf.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_specular/background.vert",
        "../shaders/shader_file/PBR/IBL_specular/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("irradiance_shader", irradiance_shader);
    scene.shader.emplace("pre_filter_shader", pre_filter_shader);
    scene.shader.emplace("brdf_shader", brdf_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();

    scene.shader["pbr_shader"].setInt("irradianceMap", 0);
    scene.shader["pbr_shader"].setInt("prefilterMap", 1);
    scene.shader["pbr_shader"].setInt("brdfLUT", 2);
    scene.shader["pbr_shader"].setVec3("albedo", 0.5f, 0.0f, 0.0f);
    scene.shader["pbr_shader"].setFloat("ao", 1.0f);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Load HDR Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/HDR/sea.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    scene.textures.emplace("irradianceMap", irradianceMap);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    scene.shader["irradiance_shader"].use();
    scene.shader["irradiance_shader"].setInt("environmentMap", 0);
    scene.shader["irradiance_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["irradiance_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minification filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    scene.textures.emplace("prefilterMap", prefilterMap);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    scene.shader["pre_filter_shader"].use();
    scene.shader["pre_filter_shader"].setInt("environmentMap", 0);
    scene.shader["pre_filter_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        scene.shader["pre_filter_shader"].setFloat("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            scene.shader["pre_filter_shader"].setMat4("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube_IBL();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("brdfLUTTexture", brdfLUTTexture);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    scene.shader["brdf_shader"].use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad_IBL();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

Scene gen_PBR_IBL_textured_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {0.0f, 0.0f, 20.0f};
    primary_cam.cameraPos = cameraPos;

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/pbr.vert",
        "../shaders/shader_file/PBR/IBL_textured/pbr.frag");

    Shader light_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/light.vert",
        "../shaders/shader_file/PBR/IBL_textured/light.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_textured/rect_to_cube.frag");

    Shader irradiance_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/irradiance.vert",
        "../shaders/shader_file/PBR/IBL_textured/irradiance.frag");

    Shader pre_filter_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/filter.vert",
        "../shaders/shader_file/PBR/IBL_textured/filter.frag");

    Shader brdf_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/brdf.vert",
        "../shaders/shader_file/PBR/IBL_textured/brdf.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/background.vert",
        "../shaders/shader_file/PBR/IBL_textured/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("irradiance_shader", irradiance_shader);
    scene.shader.emplace("pre_filter_shader", pre_filter_shader);
    scene.shader.emplace("brdf_shader", brdf_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();

    scene.shader["pbr_shader"].setInt("irradianceMap", 0);
    scene.shader["pbr_shader"].setInt("prefilterMap", 1);
    scene.shader["pbr_shader"].setInt("brdfLUT", 2);
    scene.shader["pbr_shader"].setInt("albedoMap", 3);
    scene.shader["pbr_shader"].setInt("normalMap", 4);
    scene.shader["pbr_shader"].setInt("metallicMap", 5);
    scene.shader["pbr_shader"].setInt("roughnessMap", 6);
    scene.shader["pbr_shader"].setInt("aoMap", 7);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Load PBR Texture *********************************/

    // load PBR material textures
    // --------------------------
    // rusted iron
    unsigned int ironAlbedoMap = load_textures("../textures/PBR/beaten-up-metal1-ue/albedo.png", true);
    unsigned int ironNormalMap = load_textures("../textures/PBR/beaten-up-metal1-ue/normal.png", true);
    unsigned int ironMetallicMap = load_textures("../textures/PBR/beaten-up-metal1-ue/metallic.png", true);
    unsigned int ironRoughnessMap = load_textures("../textures/PBR/beaten-up-metal1-ue/roughness.png", true);
    unsigned int ironAOMap = load_textures("../textures/PBR/beaten-up-metal1-ue/ao.png", true);
    scene.textures.emplace("ironAlbedoMap", ironAlbedoMap);
    scene.textures.emplace("ironNormalMap", ironNormalMap);
    scene.textures.emplace("ironMetallicMap", ironMetallicMap);
    scene.textures.emplace("ironRoughnessMap", ironRoughnessMap);
    scene.textures.emplace("ironAOMap", ironAOMap);
    // gold
    unsigned int goldAlbedoMap = load_textures("../textures/PBR/gold/albedo.png", true);
    unsigned int goldNormalMap = load_textures("../textures/PBR/gold/normal.png", true);
    unsigned int goldMetallicMap = load_textures("../textures/PBR/gold/metallic.png", true);
    unsigned int goldRoughnessMap = load_textures("../textures/PBR/gold/roughness.png", true);
    unsigned int goldAOMap = load_textures("../textures/PBR/gold/void_ao.png", true);
    scene.textures.emplace("goldAlbedoMap", goldAlbedoMap);
    scene.textures.emplace("goldNormalMap", goldNormalMap);
    scene.textures.emplace("goldMetallicMap", goldMetallicMap);
    scene.textures.emplace("goldRoughnessMap", goldRoughnessMap);
    scene.textures.emplace("goldAOMap", goldAOMap);

    // wall
    unsigned int wallAlbedoMap = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/albedo.png", true);
    unsigned int wallNormalMap = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/normal.png", true);
    unsigned int wallMetallicMap = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/metallic.png", true);
    unsigned int wallRoughnessMap = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/roughness.png", true);
    unsigned int wallAOMap = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/ao.png", true);
    scene.textures.emplace("wallAlbedoMap", wallAlbedoMap);
    scene.textures.emplace("wallNormalMap", wallNormalMap);
    scene.textures.emplace("wallMetallicMap", wallMetallicMap);
    scene.textures.emplace("wallRoughnessMap", wallRoughnessMap);
    scene.textures.emplace("wallAOMap", wallAOMap);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Load Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/HDR/room.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    scene.textures.emplace("irradianceMap", irradianceMap);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    scene.shader["irradiance_shader"].use();
    scene.shader["irradiance_shader"].setInt("environmentMap", 0);
    scene.shader["irradiance_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["irradiance_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minification filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    scene.textures.emplace("prefilterMap", prefilterMap);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    scene.shader["pre_filter_shader"].use();
    scene.shader["pre_filter_shader"].setInt("environmentMap", 0);
    scene.shader["pre_filter_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        scene.shader["pre_filter_shader"].setFloat("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            scene.shader["pre_filter_shader"].setMat4("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube_IBL();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("brdfLUTTexture", brdfLUTTexture);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    scene.shader["brdf_shader"].use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad_IBL();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

Scene gen_PBR_IBL_model_scene()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 cameraPos = {12.0f, 2.37f, 37.27f};
    glm::vec3 cameraFront = {-0.370f, -0.080f, -0.925f};
    primary_cam.cameraPos = cameraPos;
    primary_cam.cameraFront = cameraFront;

    /********************************* Init Shader *********************************/
    Shader pbr_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/pbr.vert",
        "../shaders/shader_file/PBR/IBL_textured/pbr.frag");

    Shader light_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/light.vert",
        "../shaders/shader_file/PBR/IBL_textured/light.frag");

    Shader rect_to_cube_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/rect_to_cube.vert",
        "../shaders/shader_file/PBR/IBL_textured/rect_to_cube.frag");

    Shader irradiance_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/irradiance.vert",
        "../shaders/shader_file/PBR/IBL_textured/irradiance.frag");

    Shader pre_filter_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/filter.vert",
        "../shaders/shader_file/PBR/IBL_textured/filter.frag");

    Shader brdf_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/brdf.vert",
        "../shaders/shader_file/PBR/IBL_textured/brdf.frag");

    Shader background_shader = Shader(
        "../shaders/shader_file/PBR/IBL_textured/background.vert",
        "../shaders/shader_file/PBR/IBL_textured/background.frag");

    scene.shader.emplace("pbr_shader", pbr_shader);
    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("rect_to_cube_shader", rect_to_cube_shader);
    scene.shader.emplace("irradiance_shader", irradiance_shader);
    scene.shader.emplace("pre_filter_shader", pre_filter_shader);
    scene.shader.emplace("brdf_shader", brdf_shader);
    scene.shader.emplace("background_shader", background_shader);

    /********************************* Init Uniform Buffer *********************************/

    scene.shader["pbr_shader"].use();

    scene.shader["pbr_shader"].setInt("irradianceMap", 0);
    scene.shader["pbr_shader"].setInt("prefilterMap", 1);
    scene.shader["pbr_shader"].setInt("brdfLUT", 2);
    scene.shader["pbr_shader"].setInt("albedoMap", 3);
    scene.shader["pbr_shader"].setInt("normalMap", 4);
    scene.shader["pbr_shader"].setInt("metallicMap", 5);
    scene.shader["pbr_shader"].setInt("roughnessMap", 6);
    scene.shader["pbr_shader"].setInt("aoMap", 7);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setInt("environmentMap", 0);

    /********************************* Load Model *********************************/
    scene.model_obj.emplace("gun", Model("../models/gun/Cerberus_LP.FBX"));
    // scene.model_obj.emplace("backpack", Model("../models/backpack/backpack.obj"));

    /********************************* Load PBR Texture *********************************/
    // 这里我们只能手动读取纹理了～
    // load PBR material textures
    // --------------------------
    // The GUN
    unsigned int gunAlbedoMap = load_textures("../textures/PBR/gun/albedo.png", false);
    unsigned int gunNormalMap = load_textures("../textures/PBR/gun/normal.png", false);
    unsigned int gunMetallicMap = load_textures("../textures/PBR/gun/metallic.png", false);
    unsigned int gunRoughnessMap = load_textures("../textures/PBR/gun/roughness.png", false);
    unsigned int gunAOMap = load_textures("../textures/PBR/gun/void_ao.png", false);
    scene.textures.emplace("gunAlbedoMap", gunAlbedoMap);
    scene.textures.emplace("gunNormalMap", gunNormalMap);
    scene.textures.emplace("gunMetallicMap", gunMetallicMap);
    scene.textures.emplace("gunRoughnessMap", gunRoughnessMap);
    scene.textures.emplace("gunAOMap", gunAOMap);

    /********************************* Init FBO *********************************/

    scene.FBO.emplace("captureFBO", 0);
    scene.RBO.emplace("captureRBO", 0);

    glGenFramebuffers(1, &scene.FBO["captureFBO"]);
    glGenRenderbuffers(1, &scene.RBO["captureRBO"]);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene.RBO["captureRBO"]);

    /********************************* Load HDR Texture *********************************/

    unsigned int hdrTexture = load_HDR_textures("../textures/HDR/room.jpg", true);
    scene.textures.emplace("hdrTexture", hdrTexture);

    /**************************** 设置 Cube Map 将绘制到哪个 FBO ****************************/

    unsigned int envCubemap; // 注意一下看看这个是否需要导入 texture emplace
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("envCubemap", envCubemap);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    scene.shader["rect_to_cube_shader"].use();
    scene.shader["rect_to_cube_shader"].setInt("equirectangularMap", 0);
    scene.shader["rect_to_cube_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["hdrTexture"]);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["rect_to_cube_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    scene.textures.emplace("irradianceMap", irradianceMap);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    scene.shader["irradiance_shader"].use();
    scene.shader["irradiance_shader"].setInt("environmentMap", 0);
    scene.shader["irradiance_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["irradiance_shader"].setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube_IBL();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minification filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    scene.textures.emplace("prefilterMap", prefilterMap);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    scene.shader["pre_filter_shader"].use();
    scene.shader["pre_filter_shader"].setInt("environmentMap", 0);
    scene.shader["pre_filter_shader"].setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        scene.shader["pre_filter_shader"].setFloat("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            scene.shader["pre_filter_shader"].setMat4("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube_IBL();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    scene.textures.emplace("brdfLUTTexture", brdfLUTTexture);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["captureFBO"]);
    glBindRenderbuffer(GL_RENDERBUFFER, scene.RBO["captureRBO"]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    scene.shader["brdf_shader"].use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad_IBL();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    //
    //
    //
    //

    /****************************  ****************************/
    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);

    // Other render option
    glEnable(GL_DEPTH_TEST); // enable depth test

    // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 使用默认模式绘制几何
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return scene;
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO_IBL = 0;
unsigned int cubeVBO_IBL = 0;
void renderCube_IBL()
{
    // initialize (if necessary)
    if (cubeVAO_IBL == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // top-left
            // front face
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
            -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
                                                                // right face
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top-right
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // top-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO_IBL);
        glGenBuffers(1, &cubeVBO_IBL);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO_IBL);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO_IBL);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO_IBL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO_IBL = 0;
unsigned int quadVBO_IBL;
void renderQuad_IBL()
{
    if (quadVAO_IBL == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,
            1.0f,
            0.0f,
            0.0f,
            1.0f,
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            -1.0f,
            0.0f,
            1.0f,
            0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO_IBL);
        glGenBuffers(1, &quadVBO_IBL);
        glBindVertexArray(quadVAO_IBL);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO_IBL);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO_IBL);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
