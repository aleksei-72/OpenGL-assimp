#ifndef HITBOX_H
#define HITBOX_H


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;

class HitBox
{
public:

    HitBox();
    HitBox(std::string fname);
    int loadFromFile(std::string fname);

    float *vertices;
    int verticesCount;
private:

};

#endif // HITBOX_H
