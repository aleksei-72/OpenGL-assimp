#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <iostream>

#define TEXTURE_LOAD_ERROR 1043633456

struct Texture
{
    std::string fname;
    GLuint t;
    int w, h;
};

Texture loadTexture(std::string filename);

#endif // TEXTURE_H
