#ifndef MESH_H
#define MESH_H
#include "global_include.h"
#include "shaders/shaders.h"


// 顶点数据结构体
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// 纹理数据结构体
struct Texture
{
    unsigned int id;
    string type;
    string path;  // we store the path of the texture to compare with other textures
};

// 网格类
class Mesh
{
public:
    // mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader &shader);

public:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};



#endif
