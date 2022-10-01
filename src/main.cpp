#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <src/gl/texture.h>
#include <src/public/public.h>
#include <src/gl/shader.h>
#include <src/3d/mesh/simpleMeshes.h>
#include <src/3d/gameObject/GameObject.h>
#include <src/gl/pixelBufferToTGA.h>
#include <src/timer/timer.h>

#include <glm/vec2.hpp>

#include <src/physics/player/playerPhysics.h>

#include <src/3d/model/Model.h>

#include <src/input/keyboard.h>
#include <src/input/mouse.h>

#include <src/fpsCounter/fpsCounter.h>
#include <src/parsers/parseConfig.h>
#include <src/parsers/parseLevel.h>

#include <src/render/RenderManager.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    Timer t;
    if (glfwInit() == GL_FALSE)
    {
        logger_error("fail for init GLFW", "");
        return 1;
    }

    try
    {
        parseInitConfig("path.ini");
        parseGraphicsConfig("graphics.ini");
        parsePlayerConfig("player.ini");
        parseOtherConfig("conf.ini");
    }
    catch (runtime_error &e)
    {
        cout << e.what();
        logger_error(e.what(), "");
        return 0;
    }

    if(graphicSettings.doubleBufferization)
    {
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glEnable(GL_DOUBLEBUFFER);
        glfwSwapInterval(1);
    }
    else
    {
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
        glDisable(GL_DOUBLEBUFFER);
    }


    GLFWwindow *window;

    {
        int x = graphicSettings.startWindowPosition.x,
            y = graphicSettings.startWindowPosition.y,
            w = graphicSettings.startWindowResolution.x,
            h = graphicSettings.startWindowResolution.y;

        if(graphicSettings.isFullScreen)
        {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            window = glfwCreateWindow(w, h, "", monitor, 0);
        }
        else
        {
            window = glfwCreateWindow(w, h, "", 0, 0);
        }

        if (!window)
        {
            logger_error("fail for create window", "fullscreen: " + string(graphicSettings.isFullScreen ? "t" : "f") +
                         " w: " + to_string(w) +
                         " h: " + to_string(h));
        }

        glfwSetWindowPos(window, x, y);
    }




    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        logger_error("fail for init GLEW", "");
        return 1;
    }

    glGetError();//fix bug with false error for glewInit();

    if (!GLEW_VERSION_3_3)
    {
        logger_error("OpenGL 3.3 is required", "");
        return 1;
    }

    logger_info("init OpenGL " + to_string(t.getElapsedTime()) + " ms", "");

    glEnable(GL_DEPTH_TEST);

    glCullFace( GL_BACK );
    glEnable(GL_CULL_FACE);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window, onKeyEvent);
    glfwSetCursorPosCallback(window, onCursorPosition);

    Shader shader;
    shader.LoadFromFile("vertex.glsl", nullptr, "fragment.glsl");

    parseLevel("levels/level1.xml");

    RenderManager render(
        {
            &shader
        }
    );

    FpsCounter fpsCounter;
    fpsCounter.init(clock());

    float frameTime = 0;

    while(!glfwWindowShouldClose(window))
    {

        updatePlayer(window, frameTime);

        glm::ivec2 resolution = {0, 0};
        glfwGetWindowSize(window, &resolution.x, &resolution.y);

        render.setResolution(resolution);
        render.setCamera(
            glm::vec3(player.position.x, player.position.y, player.position.z),
            glm::vec3(player.position.x + 1.0 * sin(player.turning.x),
                player.position.y -1.0 * tan(player.turning.y),
                player.position.z + 1.0 * cos(player.turning.x)),
            glm::vec3(0, 1, 0)
        );
        render.setFOV(graphicSettings.fov);
        render.setRenderDistance(graphicSettings.renderDistance);


        render.beginRender();
        for (std::vector<GameObject>::iterator object = manager.begin(); object != manager.end(); object++)
        {

            if (object == manager.begin())
            {
                (*(object)).rotate({0.002 * frameTime, 0.002 * frameTime, 0.002 * frameTime});
            }

            if ((*(object)).object == nullptr)
            {
                logger_error("gameobject->object is null", (*(object)).getDebugInfo());
                continue;
            }

            render.render((*(object)).object->model, (*(object)).position, (*(object)).turning);
        }
        render.endRender();


        if(graphicSettings.doubleBufferization)
            glfwSwapBuffers(window);
        else
            glFinish();

        glfwPollEvents();

        fpsCounter.frameEnd(clock());

        frameTime = fpsCounter.getCurrentFrameTime();

        if (frameTime == 0.f)
        {
            frameTime = 0.1f;
        }

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
