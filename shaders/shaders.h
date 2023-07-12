#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

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
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float v1, float v2, float v3);

public:
    // the program ID
    unsigned int ID;
};

#endif