#ifndef SCENE_H
#define SCENE_H

#include "global_include.h"
#include "shaders/shaders.h"
#include "gl_textures.h"
#include "models.h"
#include "camera.h"

// 创建一个场景，需要在本地创建，并导入到GPU中
class Scene
{
public:
    // 一个场景可以有不止一个shader文件控制，所以不应该在构造函数中传入shader路径
    Scene()
    {
        background = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        mat_shininess = 32.0f;
        mat_ambient = 2.5f;
        mat_heightScale = 0.025f;
    }

public:
    glm::vec4 background;

    std::unordered_map<std::string, Shader> shader; // 目前场景和shader是绑定的
    std::unordered_map<std::string, unsigned int> textures;
    std::unordered_map<std::string, Model> model_obj;

    float mat_shininess;
    float mat_ambient;
    float mat_heightScale;
};

Scene gen_playground_scene_p1_simple();

Scene gen_playground_scene_p2_texture();

Scene gen_playground_scene_p3_light_source();

Scene gen_playground_scene_p4_normal_mapping();

Scene gen_playground_scene_p5_height_mapping();

#endif