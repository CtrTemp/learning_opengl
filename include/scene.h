#ifndef SCENE_H
#define SCENE_H

#include "global_include.h"
#include "shaders/shaders.h"
#include "textures/gl_textures.h"
#include "models/models.h"

// 创建一个场景，需要在本地创建，并导入到GPU中
class Scene
{
public:
    // 一个场景可以有不止一个shader文件控制，所以不应该在构造函数中传入shader路径
    Scene()
    {
        background = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        trans = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }

public:
    glm::vec4 background;
    std::unordered_map<std::string, unsigned int> VAO;
    std::unordered_map<std::string, unsigned int> VBO;
    unsigned int EBO;
    glm::mat4 trans;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    std::unordered_map<std::string, Shader> shader; // 目前场景和shader是绑定的
    std::unordered_map<std::string, unsigned int> textures;
    // std::vector<>
    Model model_obj;
};

Scene gen_multi_rotating_cube_scene();

Scene gen_lighting_scene();

Scene gen_load_model_scene();

Scene gen_skybox_scene();

Scene gen_geometry_shader_scene();

Scene gen_explode_model_scene();

Scene gen_visualize_model_normal_scene();

#endif