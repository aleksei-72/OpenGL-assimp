#ifndef PUBLIC_H
#define PUBLIC_H

#include <src/logger/logger.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <src/player/Player.h>

#define logger_error(m, d) logger.error(m, d, __FILE__, __LINE__)
#define logger_info(m, d) logger.info(m, d, __FILE__, __LINE__)

using namespace glm;

struct PathSettings
{
    string basePath  = "",
        shaderPath   = "",
        meshPath     = "",
        configPath   = "",
        texturePath  = "";
};

struct GraphicSettings
{
    bool doubleBufferization = false,
        isFullScreen = false;

    float fov = 80,
          renderDistance = 250;

    ivec2 startWindowResolution,
        startWindowPosition;
};

struct PlayerSettings
{
    float speed = 0.07,
        speedBoost = 0.14;
};

struct UsersSettings
{
    float cursorSensivity = 0.0075;
};

extern Logger logger;

extern Player player;
extern UsersSettings usersSettings;
extern PlayerSettings playerSettings;

extern GraphicSettings graphicSettings;
extern PathSettings pathSettings;

#endif // PUBLIC_H
