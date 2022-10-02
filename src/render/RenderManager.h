#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include <src/constants.h>
#include <src/logger/logger.h>

#include <src/gl/shader.h>
#include <src/3d/model/Model.h>

struct ShadersList
{
    Shader *mainShader;
    Shader *postProcessingShader;
};

struct AntiAliasingConfig
{
    AntiAliasingType type;
    int value;
};

struct RenderManagerConfig
{
    ShadersList shadersList;
    AntiAliasingConfig antiAliasing;
};


struct shadersCache
{
    GLint mainShaderTexture1Pos,
        mainShaderMVPpos,
        postProcessingShaderInputTexture,
        postProcessingShaderAntiAliasingPixels;
};

struct RenderBuffers
{
    GLuint offscreenBuffer,
        offscreenTexture,
        rbo;
};

class RenderManager
{
public:

    static glm::ivec2 getCountOfPixel(int antialiasingValue);

    RenderManager(RenderManagerConfig cfg, Logger *logger);
    void setResolution(glm::ivec2 resolution);
    void setWindowSize(glm::ivec2 wsize);
    void setCamera(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up);
    void setFOV(float fov);
    void setRenderDistance(float distanse);

    void beginRender();
    void endRender();
    void render(Model *m, glm::fvec3 position, glm::fvec3 turning);

private:

    void checkGlError();
    void generateProjectionMatrix();
    void generateViewMatrix();
    void updateShaderCache();

    Logger *logger;

    shadersCache shaderCache;
    glm::fvec3 eye, center, up;

    float fov, distanse;
    RenderManagerConfig cfg;
    glm::ivec2 resolution, wsize;

    glm::mat4 projection,
        view;

    Mesh *quad;
    RenderBuffers glValues;
};

#endif // RENDER_MANAGER_H
