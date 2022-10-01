#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include <src/gl/shader.h>
#include <src/3d/model/Model.h>


struct RenderManagerConfig
{
    Shader *shader;
};

class RenderManager
{
public:

    RenderManager(RenderManagerConfig cfg);
    void setResolution(glm::ivec2 resolution);
    void setCamera(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up);
    void setFOV(float fov);
    void setRenderDistance(float distanse);

    void beginRender();
    void endRender();
    void render(Model *m, glm::fvec3 position, glm::fvec3 turning);
private:

    void generateProjectionMatrix();
    void generateViewMatrix();
    glm::fvec3 eye, center, up;

    float fov, distanse;
    RenderManagerConfig cfg;
    glm::ivec2 resolution;

    glm::mat4 projection,
        view;
};

#endif // RENDER_MANAGER_H
