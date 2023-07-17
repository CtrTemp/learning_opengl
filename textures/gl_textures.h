#ifndef GL_TEXTURES_H
#define GL_TEXTURES_H

#include "global_include.h"

unsigned int load_textures(std::string texture_src);

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);

unsigned int loadCubemap(vector<std::string> faces);

extern vector<std::string> faces;

#endif