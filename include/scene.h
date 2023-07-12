#ifndef SCENE_H
#define SCENE_H

#include "global_include.h"
#include "shaders/shaders.h"

// 创建一个场景，需要在本地创建，并导入到GPU中
class Scene
{
public:
    // 创建场景时必须要传入其对应的shader
    Scene(std::string vert_shader, std::string frag_shader)
    {
        VAO = 0;
        VBO = 0;
        EBO = 0;
        trans = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
        shader = Shader(vert_shader.c_str(), frag_shader.c_str());
    }

public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    glm::mat4 trans;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    Shader shader; // 目前场景和shader是绑定的
    std::vector<unsigned int> textures;
};

Scene gen_multi_rotating_cube_scene();

#endif