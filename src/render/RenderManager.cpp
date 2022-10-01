#include <src/render/RenderManager.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

RenderManager::RenderManager(RenderManagerConfig cfg)
{
    this->cfg = cfg;
}

void RenderManager::setResolution(ivec2 resolution)
{
    this->resolution = resolution;
}

void RenderManager::setCamera(fvec3 eye, fvec3 center, fvec3 up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
}

void RenderManager::setFOV(float fov)
{
    this->fov = fov;
}

void RenderManager::setRenderDistance(float distanse)
{
    this->distanse = distanse;
}

void RenderManager::generateProjectionMatrix()
{
    this->projection = perspective(
        (float)radians(this->fov),
        (float)this->resolution.x / this->resolution.y,
        (float)0.1f,
        (float)this->distanse
    );
}

void RenderManager::generateViewMatrix()
{
    this->view = lookAt(
        this->eye,
        this->center,
        this->up
    );
}

void RenderManager::beginRender()
{
    generateProjectionMatrix();
    generateViewMatrix();

    glViewport(0, 0, resolution.x, resolution.y);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glUseProgram(this->cfg.shader->programm);
}

void RenderManager::endRender()
{
    // postProcessing
}

void RenderManager::render(Model *m, glm::fvec3 position, glm::fvec3 turning)
{
    mat4 model = glm::translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    model = rotate(model, turning.x, vec3(1, 0, 0));
    model = rotate(model, turning.y, vec3(0, 1, 0));
    model = rotate(model, turning.z, vec3(0, 0, 1));

    glm::mat4 MVP = this->projection * this->view * model;



    // @TODO: save uniform positions as variable
    glUniform1i(this->cfg.shader->getUniformPos("mainTexture"), 0);
    glUniformMatrix4fv(this->cfg.shader->getUniformPos("mvp"), 1, GL_FALSE, &MVP[0][0]);

    for (Mesh mesh: m->meshes)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        // @TODO one mesh can has many diffuse textures
        glBindTexture(GL_TEXTURE_2D, mesh.diffuseTextures.front()->t);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.triangleCount);
    }
}
