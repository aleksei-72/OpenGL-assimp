#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <src/3d/object/Object.h>
#include <src/gl/texture.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;

class GameObject
{
public:
    unsigned int id;

    GameObject();

    Object *object = nullptr;

    vec3 position = {0, 0, 0},
         turning = {0, 0, 0};

    void rotate(vec3 delta);

    std::string getDebugInfo();
private:

    void normalizeDurning();
    float normalizeOneAngle(float angle);
};

#endif // GAME_OBJECT_H
