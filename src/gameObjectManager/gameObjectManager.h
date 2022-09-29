#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <iostream>
#include <map>
#include <vector>

#include <glm/vec3.hpp>
#include <src/gl/texture.h>
#include <src/3d/model/Model.h>
#include <src/3d/object/Object.h>
#include <src/3d/hitbox/HitBox.h>
#include <src/3d/gameObject/GameObject.h>

class GameObjectManager
{
public:

    Texture *getTexture(std::string fname);
    Model *getModel(std::string name);
    Object *get3dObject(std::string name);

    std::vector<GameObject>::iterator begin();
    std::vector<GameObject>::iterator end();

    Model* addModel(std::string name, Model m);
    Object* addObject(std::string name, Object o);

    GameObject* spawn(std::string objectName, glm::vec3 position, glm::vec3 turning = {0, 0, 0});
private:
    std::map<std::string, Texture> textureStorage;
    std::map<std::string, Model> modelStorage;
    std::map<std::string, Object> objectStorage;
    std::vector<GameObject> objects;

    unsigned int nextObjectId = 0;
};

#endif// GAME_OBJECT_MANAGER_H
