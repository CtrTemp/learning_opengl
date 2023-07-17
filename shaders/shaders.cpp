
#include "shaders/shaders.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 验证是否读入了正确的shader文件
    // std::cout << "vertex shader = " << vertexCode << std::endl;
    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    // 将 shader source 字符串绑定到 vertexShader 实例
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex); // 使用命令对该字符串在运行时进行编译
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }

    // similiar for Fragment Shader

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 对编译结果进行check
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID); // 添加两个shader程序片段，并使用 glLinkProgram 函数链接他们
    // 对该着色器程序是否创建成功进行检测
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER PROGRAM::COMPILATION_FAILED\n");
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        gShaderFile.open(geometryPath);
        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        gShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geometryCode = gShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    // 验证是否读入了正确的shader文件
    // std::cout << "vertex shader = " << vertexCode << std::endl;
    // 2. compile shaders
    unsigned int vertex, fragment, geometry;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    // 将 shader source 字符串绑定到 vertexShader 实例
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex); // 使用命令对该字符串在运行时进行编译
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }

    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 对编译结果进行check
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }

    // similiar for Geometry Shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    // 对编译结果进行check
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n");
    }

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glAttachShader(ID, geometry);
    glLinkProgram(ID); // 添加两个shader程序片段，并使用 glLinkProgram 函数链接他们
    // 对该着色器程序是否创建成功进行检测
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw std::runtime_error("ERROR::SHADER PROGRAM::COMPILATION_FAILED\n");
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, float v1, float v2)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
}

void Shader::setVec2(const std::string &name, glm::vec2 vec)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y);
}

void Shader::setVec3(const std::string &name, float v1, float v2, float v3)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}

void Shader::setVec3(const std::string &name, glm::vec3 vec)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setMat4(const std::string &name, glm::mat4 mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}
