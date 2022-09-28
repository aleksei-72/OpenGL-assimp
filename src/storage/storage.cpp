#include <src/storage/storage.h>

using namespace std;

std::map<std::string, Texture> textureStorage;
std::map<std::string, Model> modelStorage;

std::map<std::string, Object> objectStorage;

Texture *getTexture(string fname)
{
    if (textureStorage.find(fname) == textureStorage.end())
        textureStorage[fname] = loadTexture(fname);

    return &(textureStorage[fname]);
}


Model *getModel(string name)
{
    if (modelStorage.find(name) == modelStorage.end())
    {
        return nullptr;
    }

    return &(modelStorage[name]);
}

Object *get3dObject(string name)
{
    if (objectStorage.find(name) == objectStorage.end())
    {
        return nullptr;
    }

    return &(objectStorage[name]);
}
