#include <src/3d/gameObject/GameObject.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <src/3d/mesh/simpleMeshes.h>

#include <src/public/public.h>
#include <src/constants.h>
#include <iostream>

using namespace std;

unsigned int GameObject::nextObjectId = 0;

GameObject::GameObject()
{
    id = nextObjectId;
    nextObjectId ++;
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

string GameObject::getDebugInfo()
{
    string result = "id: " + to_string(id);

    if (object != nullptr && object->model != nullptr)
        result += "\nobject->model: '" + object->model->getDebugInfo() + "'";

    return result;
}
