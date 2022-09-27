#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <src/public/public.h>

vec2 mouseLastPosition = {-9999, -9999};

void onCursorPosition(GLFWwindow* window, double xpos, double ypos)
{
    vec2 cursor = {xpos, ypos};

    if (mouseLastPosition.x == -9999 && mouseLastPosition.y == -9999)
        mouseLastPosition = cursor;

    player.rotate({mouseLastPosition.x - cursor.x, cursor.y - mouseLastPosition.y, 0});

    mouseLastPosition = cursor;
}
