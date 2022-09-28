#include <src/storage/storage.h>

using namespace std;

std::map<std::string, Texture> textureStorage;
std::map<std::string, Model> modelStorage;

Texture *getTexture(string fname)
{
    if (textureStorage.find(fname) == textureStorage.end())
        textureStorage[fname] = loadTexture(fname);

    return &(textureStorage[fname]);
}


Model *getModel(string fname, string texture)
{
    if (modelStorage.find(fname) == modelStorage.end())
    {
        modelStorage[fname] = Model(fname);
        modelStorage[fname].texture = getTexture(texture);
    }

    return &(modelStorage[fname]);
}
