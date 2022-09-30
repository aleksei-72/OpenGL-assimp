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
#include <iostream>
#include <vector>

using namespace glm;

class Model
{
public:

    Model();
    Model(std::string fname, float scale = 1.f);
    int loadFromFile(std::string fname, float scale = 1.f);

    std::vector <Mesh> meshes;

    std::string getDebugInfo();
private:

    std::string originalFname;
    std::string folderPath;
    void processNode(aiNode *node, const aiScene *scene, float scale);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, float scale);

    std::vector<std::string> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
};

#endif // MODEL_H
