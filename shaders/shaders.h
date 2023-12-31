#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader() {}
    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);
    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float v1, float v2, float v3);
    void setVec3(const std::string &name, glm::vec3 vec);
    void setVec2(const std::string &name, float v1, float v2);
    void setVec2(const std::string &name, glm::vec2 vec);
    void setMat3(const std::string &name, glm::mat3 mat3);
    void setMat4(const std::string &name, glm::mat4 mat4);

public:
    // the program ID
    unsigned int ID;
};

#endif