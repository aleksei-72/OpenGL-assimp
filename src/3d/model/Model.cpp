#include <src/3d/model/Model.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <src/3d/mesh/simpleMeshes.h>

#include <src/public/public.h>
#include <src/constants.h>

using namespace std;

Model::Model()
{

}

Model::Model(string fname, float scale)
{

    loadFromFile(fname, scale);
}

int Model::loadFromFile(string fname, float scale)
{
    // https://learnopengl.com/Model
    originalFname = fname;

    size_t pos = fname.find_last_of('/');
    if (pos != fname.npos)
    {
        folderPath = fname.substr(0, pos);
    }

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pathSettings.basePath + pathSettings.meshPath + fname, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        logger_error("Assimp::Error", importer.GetErrorString());
    }

    logger_info("Read model '" + fname + "' success", "");
    processNode(scene->mRootNode, scene, scale);

    return 0;
}

void Model::processNode(aiNode *node, const aiScene *scene, float scale)
{

    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene, scale));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, scale);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene, float scale)
{
    vector<Vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 position;
        position.x = mesh->mVertices[i].x * scale;
        position.y = mesh->mVertices[i].y * scale;
        position.z = mesh->mVertices[i].z * scale;

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

    Mesh m(vertices);

    if (mesh->mMaterialIndex != 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);

        for(string fname: diffuseMaps)
        {
            Texture *t = manager.getTexture((folderPath.length() ? folderPath + "/" : "") + fname);

            m.diffuseTextures.push_back(t);
        }

    }
    return m;
}

vector<string> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    vector<string> textureNames;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString fname;
        mat->GetTexture(type, i, &fname);

        textureNames.push_back(string(fname.C_Str()));
    }
    return textureNames;
}


string Model::getDebugInfo()
{
    return "originalFname: " + originalFname;
}
