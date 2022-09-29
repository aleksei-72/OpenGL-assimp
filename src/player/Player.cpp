#include <src/player/Player.h>
#include <src/public/public.h>
#include <src/constants.h>
#include <cmath>

using namespace std;

void Player::rotate(vec3 delta)
{
    turning += delta * usersSettings.cursorSensivity;

    normalizeDurning();
}
void Player::move(vec3 delta)
{
    position += delta;
}


void Player::normalizeDurning()
{
    turning.x = normalizeOneAngle(turning.x);

    turning.y = std::min(1.35f, turning.y);
    turning.y = std::max(-1.35f, turning.y);
}

float Player::normalizeOneAngle(float angle)
{
    int sign = angle / abs(angle);

    while (abs(angle) > 2 * PI)
    {
        angle -= sign * 2 * PI;
    }

    return angle;
}
