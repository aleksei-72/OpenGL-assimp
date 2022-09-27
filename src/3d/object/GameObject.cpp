#include <src/3d/object/GameObject.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <src/3d/mesh/simpleMeshes.h>

#include <src/public/public.h>
#include <src/constants.h>
#include <iostream>

GameObject::GameObject(std::string filename)
{

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pathSettings.basePath + pathSettings.meshPath + filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        logger.error("Assimp::Error", importer.GetErrorString());
    }

    processNode(scene->mRootNode, scene);
}

void GameObject::processNode(aiNode *node, const aiScene *scene)
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

Mesh GameObject::processMesh(aiMesh *mesh, const aiScene *scene)
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

glm::mat4 GameObject::getModelMatrix()
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));

    model = glm::rotate(model, turning.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, turning.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, turning.z, glm::vec3(0, 0, 1));

    return model;
}

void GameObject::rotate(vec3 delta)
{
    turning += delta;

    normalizeDurning();
}

void GameObject::normalizeDurning()
{
    turning.x = normalizeOneAngle(turning.x);
    turning.y = normalizeOneAngle(turning.y);
    turning.z = normalizeOneAngle(turning.z);
}

float GameObject::normalizeOneAngle(float angle)
{
    int sign = angle / abs(angle);

    while (abs(angle) > 2 * PI)
    {
        angle -= sign * 2 * PI;
    }

    return angle;
}
