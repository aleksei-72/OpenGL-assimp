#ifndef OBJECT_H
#define OBJECT_H

#include <src/3d/model/Model.h>
#include <src/3d/hitbox/HitBox.h>
#include <src/gl/texture.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;


enum physicsMode {
    none,
    solidBoby
};

class Object
{
public:

    Object();

    Model *model = nullptr;

    HitBox *hitbox = nullptr;

    physicsMode physicsMode = solidBoby;

private:
};

#endif // OBJECT_H
