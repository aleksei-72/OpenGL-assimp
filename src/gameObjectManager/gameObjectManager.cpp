#include <src/gameObjectManager/gameObjectManager.h>

using namespace std;
using namespace glm;


Texture *GameObjectManager::getTexture(string fname)
{
    if (textureStorage.find(fname) == textureStorage.end())
        textureStorage[fname] = loadTexture(fname);

    return &(textureStorage[fname]);
}


Model *GameObjectManager::getModel(string name)
{
    if (modelStorage.find(name) == modelStorage.end())
    {
        return nullptr;
    }

    return &(modelStorage[name]);
}

Object *GameObjectManager::get3dObject(string name)
{
    if (objectStorage.find(name) == objectStorage.end())
    {
        return nullptr;
    }

    return &(objectStorage[name]);
}

std::vector<GameObject>::iterator GameObjectManager::begin()
{
    return objects.begin();
}

std::vector<GameObject>::iterator GameObjectManager::end()
{
    return objects.end();
}

Model* GameObjectManager::addModel(std::string name, Model m)
{
    if (modelStorage.find(name) != modelStorage.end())
    {
        throw new runtime_error("Model with name '" + name + "' already exists");
    }

    if (m.meshes.size() == 0)
    {
        throw new runtime_error("Attemp to save empty model as name '" + name + "'");
    }

    modelStorage[name] = m;

    return &(modelStorage[name]);
}

Object* GameObjectManager::addObject(std::string name, Object o)
{
    if (objectStorage.find(name) != objectStorage.end())
    {
        throw new runtime_error("Model with name '" + name + "' already exists");
    }

    if (o.model == nullptr)
    {
        throw new runtime_error("Attemp to save object without model as name '" + name + "'");
    }

    if (o.hitbox == nullptr && o.physicsMode == solidBoby)
    {
        throw new runtime_error("Attemp to save model without hitbox and physicsMode 'solidBoby' as name '" + name + "'");
    }

    objectStorage[name] = o;

    return &(objectStorage[name]);
}

GameObject* GameObjectManager::spawn(std::string objectName, vec3 position, vec3 turning)
{
    GameObject obj = GameObject();

    obj.id = nextObjectId;
    nextObjectId++;

    obj.object = get3dObject(objectName);
    obj.position = position;
    obj.rotate(turning);
    objects.push_back(obj);
}
