#include <src/3d/model/Model.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <src/3d/mesh/simpleMeshes.h>

#include <src/public/public.h>
#include <src/constants.h>
#include <iostream>


Model::Model()
{

}

Model::Model(std::string fname)
{

    loadFromFile(fname);
}

int Model::loadFromFile(std::string fname)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pathSettings.basePath + pathSettings.meshPath + fname, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        logger_error("Assimp::Error", importer.GetErrorString());
    }

    logger_info("Read model '" + fname + "' success", "");
    processNode(scene->mRootNode, scene);

    return 0;
}

void Model::processNode(aiNode *node, const aiScene *scene)
{

    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;

        vertex.position = position;



        glm::vec2 texCoords = {0, 0};

        if (mesh->mTextureCoords[0])
        {
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        vertex.texCoords = texCoords;


        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;

        vertex.normal = normal;


        vertices.push_back(vertex);
    }

    return Mesh(vertices);
}

