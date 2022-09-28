#ifndef MODEL_H
#define MODEL_H

#include <src/3d/mesh/Mesh.h>
#include <src/gl/texture.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;

class Model
{
public:

    Model();
    Model(std::string fname);
    int loadFromFile(std::string fname);

    std::vector <Mesh> meshes;
    Texture *texture;

private:

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif // MODEL_H
