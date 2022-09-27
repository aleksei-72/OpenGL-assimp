#ifndef PLAYER_H
#define PLAYER_H

#include <glm/vec3.hpp>

using namespace glm;

class Player
{

public:

    vec3 position = {2, 2.4, -3.5},
         turning = {-0.7, 0.35, 0};

    void rotate(vec3 delta);
    void move(vec3 delta);

private:

    void normalizeDurning();
    float normalizeOneAngle(float angle);
};
#endif // PLAYER_H
