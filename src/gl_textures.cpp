#include "gl_textures.h"
// 这里转而使用 stb_image 库进行调试，放弃 SOIL 库
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // header only lib 在源文件中导入

// 全局 texture 变量
vector<std::string> faces{
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"};
// unsigned int cubemapTexture = loadCubemap(faces);

// 文中提到确实这样导入的纹理数据是上下颠倒的，，
unsigned int load_textures(std::string texture_src, bool vertical_flip)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(vertical_flip); // 使用这个语句将在读入纹理时将其上下颠倒。

    for (size_t i = 0; i < texture_src.size(); i++)
    {
        if (texture_src[i] == '\\')
        {
            texture_src[i] = '/';
        }
    }

    unsigned char *data = stbi_load(texture_src.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Own loader : Texture failed to load at path: " << texture_src << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int load_HDR_textures(std::string texture_src, bool vertical_flip)
{
    unsigned int HDRtextureID;
    glGenTextures(1, &HDRtextureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(vertical_flip); // 使用这个语句将在读入纹理时将其上下颠倒。

    for (size_t i = 0; i < texture_src.size(); i++)
    {
        if (texture_src[i] == '\\')
        {
            texture_src[i] = '/';
        }
    }

    float *data = stbi_loadf(texture_src.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, HDRtextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "HDR loader : Texture failed to load at path: " << texture_src << std::endl;
        stbi_image_free(data);
    }

    return HDRtextureID;
}

// {

//     // 纹理坐标的 s t 两个参数 对应直角坐标系下的 x y 并无区别（如果是3D纹理则还有第三维r对应z）
//     // 但是这里为啥要对两个坐标分别设置？等之后出图后进行效果测试
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//     // 选择纹理环绕方式
//     // GL_REPEAT            默认重复
//     // GL_MIRRORED_REPEAT   镜像重复
//     // GL_CLAMP_TO_EDGE     纹理坐标被约束在0～1之间，超出的部分将会使用边缘值填充
//     // GL_CLAMP_TO_BORDER   超出坐标的值将使用用户设定值填充，使用方式略有不同，如下：
//     // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
//     // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

//     // 纹理插值方式的设置
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 视角缩小 zoom out 的时候如何插值
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 视角放大 zoom in 的时候如何插值
//     // GL_NEAREST pixel值将取距离最近的一个 Texel 的值 （多产生 8 bit 像素风格的图）
//     // GL_LINEAR 纹理将对周边的四个 Texel 进行求平均 （多产生更加平滑的图案边缘）
//     // 还有一下四种配合方式，使用MipMap的插值方式
//     // MIPMAP 前面的 LINEAR/NEAREST 参数表示使用的纹理级别的方式： LINEAR 表示采用两个纹理级别之间的线性插值；NEAREST表示使用最邻近的纹理级别
//     // MIPMAP 后面的 LINEAR/NEAREST 参数表示像素采样 Texel 的方式： 解释与上面的 GL_NEAREST/GL_LINEAR 相同
//     // GL_LINEAR_MIPMAP_LINEAR、 GL_NEAREST_MIPMAP_LINEAR、 GL_LINEAR_MIPMAP_NEAREST、 GL_NEAREST_MIPMAP_NEAREST、
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // 以上注意一个常见错误就是将放大插值配置为MIPMAP相关的选项，但这会导致报错
//     // 这是因为仅在视角缩小时 OpenGL 才会使用MIPMAP（多级“渐远”纹理），放大时不应用该选项！

// }

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true); // 使用这个语句将在读入纹理时将其上下颠倒。

    // 这里需要注意以下反斜杠的问题，Linux 系统下无法正确识别，故在此做替换
    for (size_t i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '\\')
        {
            filename[i] = '/';
        }
    }

    // 修正后再进行读取一般就可以得到正确的读取结果，不再会报错找不到文件。
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    // throw std::runtime_error("ha");
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Temp loader : Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        if (i == 2 || i == 3)
        {
            stbi_set_flip_vertically_on_load(false); // 使用这个语句将在读入纹理时将其上下颠倒。
        }
        else
        {
            stbi_set_flip_vertically_on_load(false);
        }
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}