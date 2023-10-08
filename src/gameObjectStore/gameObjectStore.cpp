#include "gameObjectStore.h"

GameObjectStore::GameObjectStore()
{

}

GameObject *GameObjectStore::store(GameObject object)
{
    GameObject obj = object;
    obj.id = this->nextObjectId;
    this->nextObjectId ++;

    this->objects.push_back(obj);

    return &(*this->endObjects());
}

std::vector<GameObject>::iterator GameObjectStore::beginObjects()
{
    return this->objects.begin();
}

std::vector<GameObject>::iterator GameObjectStore::endObjects()
{
    return this->objects.end();
}
