#include "scene.h"

Scene gen_playground_scene_p1_simple()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/

    Shader obj_shader = Shader(
        "../shaders/playground/phase01/obj.vert",
        "../shaders/playground/phase01/obj.frag");

    scene.shader.emplace("obj_shader", obj_shader);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_playground_scene_p2_texture()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/

    Shader obj_shader = Shader(
        "../shaders/playground/phase02_texture_mapping/obj.vert",
        "../shaders/playground/phase02_texture_mapping/obj.frag");

    scene.shader.emplace("obj_shader", obj_shader);

    /*********************************** Load Texture ***********************************/

    unsigned int floor_tex = load_textures("../textures/floor.jpg", true);
    unsigned int box_tex = load_textures("../textures/box.png", true);
    scene.textures.emplace("floor_tex", floor_tex);
    scene.textures.emplace("box_tex", box_tex);

    /******************************** Configure Texture ********************************/
    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setInt("tex", 0);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_playground_scene_p3_light_source()
{
    Scene scene;

    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/

    Shader obj_shader = Shader(
        "../shaders/playground/phase03_light_source/obj.vert",
        "../shaders/playground/phase03_light_source/obj.frag");
    Shader light_shader = Shader(
        "../shaders/playground/phase03_light_source/light.vert",
        "../shaders/playground/phase03_light_source/light.frag");

    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("light_shader", light_shader);

    /*********************************** Load Texture ***********************************/

    unsigned int floor_tex = load_textures("../textures/floor.jpg", true);
    unsigned int box_tex = load_textures("../textures/box.png", true);
    scene.textures.emplace("floor_tex", floor_tex);
    scene.textures.emplace("box_tex", box_tex);

    /******************************** Configure Texture ********************************/
    scene.shader["obj_shader"].use();
    // scene.shader["obj_shader"].setInt("tex", 0);
    scene.shader["obj_shader"].setInt("material.diffuse", 0);
    // scene.shader["obj_shader"].setFloat("material.shininess", 0.0f);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_playground_scene_p4_normal_mapping()
{
    Scene scene;
    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/
    Shader box_shader = Shader(
        "../shaders/playground/phase04_normal_mapping/box.vert",
        "../shaders/playground/phase04_normal_mapping/box.frag");

    Shader plane_shader = Shader(
        "../shaders/playground/phase04_normal_mapping/plane.vert",
        "../shaders/playground/phase04_normal_mapping/plane.frag");

    Shader light_shader = Shader(
        "../shaders/playground/phase04_normal_mapping/light.vert",
        "../shaders/playground/phase04_normal_mapping/light.frag");

    scene.shader.emplace("box_shader", box_shader);
    scene.shader.emplace("plane_shader", plane_shader);
    scene.shader.emplace("light_shader", light_shader);

    /*********************************** Load Texture ***********************************/
    unsigned int plane_diffuse_tex = load_textures("../textures/PBR/wall/albedo.png", true);
    unsigned int plane_normal_tex = load_textures("../textures/PBR/wall/normal.png", true);
    unsigned int box_diffuse_tex = load_textures("../textures/box.png", true);
    unsigned int box_specular_tex = load_textures("../textures/mental_frame.png", true);
    scene.textures.emplace("plane_diffuse_tex", plane_diffuse_tex);
    scene.textures.emplace("plane_normal_tex", plane_normal_tex);
    scene.textures.emplace("box_diffuse_tex", box_diffuse_tex);
    scene.textures.emplace("box_specular_tex", box_specular_tex);

    /******************************** Configure Texture ********************************/
    scene.shader["box_shader"].use();
    scene.shader["box_shader"].setInt("material.diffuseMap", 0);
    scene.shader["box_shader"].setInt("material.specularMap", 1);

    scene.shader["plane_shader"].use();
    scene.shader["plane_shader"].setInt("material.diffuseMap", 0);
    scene.shader["plane_shader"].setInt("material.normalMap", 1);

    // scene.shader["obj_shader"].setFloat("material.shininess", 0.0f);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_playground_scene_p5_height_mapping()
{
    Scene scene;
    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/
    Shader light_shader = Shader(
        "../shaders/playground/phase05_normal_mapping/light.vert",
        "../shaders/playground/phase05_normal_mapping/light.frag");

    Shader obj_shader = Shader(
        "../shaders/playground/phase05_height_mapping/obj.vert",
        "../shaders/playground/phase05_height_mapping/obj.frag");

    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("obj_shader", obj_shader);

    /*********************************** Load Texture ***********************************/
    // unsigned int plane_diffuse_tex = load_textures("../textures/PBR/wall/albedo.png", true);
    // unsigned int plane_normal_tex = load_textures("../textures/PBR/wall/normal.png", true);
    // unsigned int plane_height_tex = load_textures("../textures/PBR/wall/depth.png", true);

    // unsigned int plane_diffuse_tex = load_textures("../textures/height_mapping/bricks2.jpg", true);
    // unsigned int plane_normal_tex = load_textures("../textures/height_mapping/bricks2_normal.jpg", true);
    // unsigned int plane_height_tex = load_textures("../textures/height_mapping/bricks2_disp.jpg", true);

    // unsigned int plane_diffuse_tex = load_textures("../textures/PBR/vines-ue/albedo.png", true);
    // unsigned int plane_specular_tex = load_textures("../textures/PBR/vines-ue/metallic.png", true);
    // unsigned int plane_normal_tex = load_textures("../textures/PBR/vines-ue/normal.png", true);
    // unsigned int plane_height_tex = load_textures("../textures/PBR/vines-ue/depth.png", true);

    unsigned int plane_diffuse_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/albedo.png", true);
    unsigned int plane_specular_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/metallic.png", true);
    unsigned int plane_normal_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/normal.png", true);
    unsigned int plane_height_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/depth.png", true);

    unsigned int box_diffuse_tex = load_textures("../textures/box.png", true);
    unsigned int box_specular_tex = load_textures("../textures/mental_frame.png", true);

    scene.textures.emplace("plane_diffuse_tex", plane_diffuse_tex);
    scene.textures.emplace("plane_specular_tex", plane_specular_tex);
    scene.textures.emplace("plane_normal_tex", plane_normal_tex);
    scene.textures.emplace("plane_height_tex", plane_height_tex);
    scene.textures.emplace("box_diffuse_tex", box_diffuse_tex);
    scene.textures.emplace("box_specular_tex", box_specular_tex);

    /******************************** Configure Texture ********************************/

    // scene.shader["obj_shader"].setFloat("material.shininess", 0.0f);

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}

Scene gen_playground_scene_p6_shadow_mapping()
{
    Scene scene;
    // 更改背景色
    scene.background = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 相机初始化坐标更改
    glm::vec3 cameraPos = {5.0f, 2.0f, 5.0f};
    primary_cam.cameraPos = cameraPos;

    /*********************************** Load Shader ***********************************/
    Shader light_shader = Shader(
        "../shaders/playground/phase06_shadow_mapping/light.vert",
        "../shaders/playground/phase06_shadow_mapping/light.frag");

    Shader obj_shader = Shader(
        "../shaders/playground/phase06_shadow_mapping/obj.vert",
        "../shaders/playground/phase06_shadow_mapping/obj.frag");

    Shader depth_shader = Shader(
        "../shaders/playground/phase06_shadow_mapping/obj.vert",
        "../shaders/playground/phase06_shadow_mapping/obj.frag");

    scene.shader.emplace("light_shader", light_shader);
    scene.shader.emplace("obj_shader", obj_shader);
    scene.shader.emplace("depth_shader", depth_shader);

    /*********************************** Load Texture ***********************************/
    unsigned int plane_diffuse_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/albedo.png", true);
    unsigned int plane_specular_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/metallic.png", true);
    unsigned int plane_normal_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/normal.png", true);
    unsigned int plane_height_tex = load_textures("../textures/PBR/sloppy-mortar-bricks-ue/depth.png", true);

    unsigned int box_diffuse_tex = load_textures("../textures/box.png", true);
    unsigned int box_specular_tex = load_textures("../textures/mental_frame.png", true);

    scene.textures.emplace("plane_diffuse_tex", plane_diffuse_tex);
    scene.textures.emplace("plane_specular_tex", plane_specular_tex);
    scene.textures.emplace("plane_normal_tex", plane_normal_tex);
    scene.textures.emplace("plane_height_tex", plane_height_tex);
    
    scene.textures.emplace("box_diffuse_tex", box_diffuse_tex);
    scene.textures.emplace("box_specular_tex", box_specular_tex);

    /************************ Depth Map ************************/
    // 创建深度图相关的 Frame Buffer Object

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

    // depth test
    glEnable(GL_DEPTH_TEST); // enable depth test
    // Other render option
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式进行绘制
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default ： 使用默认模式绘制几何

    return scene;
}
