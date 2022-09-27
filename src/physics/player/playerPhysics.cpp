#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/public/public.h>

#include <src/constants.h>
#include <cmath>

#include <glm/vec3.hpp>

void updatePlayer(GLFWwindow* window, float elapsedTime)
{
    float speed = playerSettings.speed * elapsedTime;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed = playerSettings.speedBoost * elapsedTime;


    vec3 delta = {0, 0, 0};

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        delta.x += speed*sin(player.turning.x);
        delta.y += -speed*tan(player.turning.y);
        delta.z += speed*cos(player.turning.x);
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        delta.y += speed;
    }

    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        delta.y += -speed;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        delta.x -= speed*sin(player.turning.x);
        delta.y -= -speed*tan(player.turning.y);
        delta.z -= speed*cos(player.turning.x);
    }


    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        delta.x += speed*sin(player.turning.x - 1.5708);
        delta.z += speed*cos(player.turning.x - 1.5708);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        delta.x += speed*sin(player.turning.x + 1.5708);
        delta.z += speed*cos(player.turning.x + 1.5708);
    }

    player.move(delta);
}
