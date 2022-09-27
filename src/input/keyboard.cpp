#include <src/input/keyboard.h>

#include <iostream>

void onKeyEvent( GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::exit(0);
    }
}
