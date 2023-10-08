#ifndef GAMEOBJECTSTORE_H
#define GAMEOBJECTSTORE_H

#include <vector>
#include <src/3d/gameObject/GameObject.h>

class GameObjectStore
{
public:
    GameObjectStore();
    GameObject *store(GameObject object);

    std::vector<GameObject>::iterator beginObjects();
    std::vector<GameObject>::iterator endObjects();
private:
    unsigned int nextObjectId = 0;
    std::vector<GameObject> objects;
};

#endif // GAMEOBJECTSTORE_H
