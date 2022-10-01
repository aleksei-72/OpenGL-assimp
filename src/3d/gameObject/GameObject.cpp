#include <src/3d/gameObject/GameObject.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <src/3d/mesh/simpleMeshes.h>

#include <src/public/public.h>
#include <src/constants.h>
#include <iostream>

using namespace std;


GameObject::GameObject()
{

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
