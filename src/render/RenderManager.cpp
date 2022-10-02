#include <src/render/RenderManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <src/3d/mesh/Mesh.h>
#include <src/3d/mesh/simpleMeshes.h>

using namespace glm;

RenderManager::RenderManager(RenderManagerConfig cfg, Logger *logger)
{
    this->cfg = cfg;
    this->logger = logger;
    this->quad = new Mesh(generateCube(1.f));
    updateShaderCache();
}

void RenderManager::setResolution(ivec2 resolution)
{
    this->resolution = resolution;
}

void RenderManager::setWindowSize(glm::ivec2 wsize)
{
    this->wsize = wsize;
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

ivec2 RenderManager::getCountOfPixel(int antialiasingValue)
{
    if (antialiasingValue == 0)
        return vec2(1, 1);

    for (int i = 1; i <= 256; i += i)
    {
        for (int j = i; j <= i*2; j += j)
        {
            if (i * j == antialiasingValue)
                return vec2(j, i);
        }
    }

    return vec2(0, 0);
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

void RenderManager::updateShaderCache()
{
    this->shaderCache.mainShaderTexture1Pos = this->cfg.shadersList.mainShader->getUniformPos("texture1");
    this->shaderCache.mainShaderMVPpos = this->cfg.shadersList.mainShader->getUniformPos("mvp");
    this->shaderCache.postProcessingShaderInputTexture = this->cfg.shadersList.postProcessingShader->getUniformPos("texture");
    this->shaderCache.postProcessingShaderAntiAliasingPixels = this->cfg.shadersList.postProcessingShader->getUniformPos("aaPixels");
}

void RenderManager::checkGlError()
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR)
        logger->error("OpenGL error: " + to_string(e), "");
}

void RenderManager::beginRender()
{
    generateProjectionMatrix();
    generateViewMatrix();

    //поддержка alpha - канала
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    glCullFace( GL_BACK );
    glEnable(GL_CULL_FACE);

    checkGlError();
    if (this->cfg.antiAliasing.type == noneAA)
    {
        glViewport(0, 0, resolution.x, resolution.y);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glUseProgram(this->cfg.shadersList.mainShader->programm);
        return;
    }


    glGenFramebuffers(1, &this->glValues.offscreenBuffer);
        checkGlError();
    glBindFramebuffer(GL_FRAMEBUFFER, this->glValues.offscreenBuffer);


    glGenTextures(1, &this->glValues.offscreenTexture);
    glBindTexture(GL_TEXTURE_2D, this->glValues.offscreenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->glValues.offscreenTexture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        logger->error("OpenGl error", "frameBuffer is not complete", __FILE__, __LINE__);

    glBindFramebuffer(GL_FRAMEBUFFER, this->glValues.offscreenBuffer);

    glGenRenderbuffers(1, &this->glValues.rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, this->glValues.rbo);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, resolution.x, resolution.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->glValues.rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, this->glValues.offscreenBuffer);

    glViewport(0, 0, resolution.x, resolution.y);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glUseProgram(this->cfg.shadersList.mainShader->programm);

    //checkGlError();
}


void RenderManager::endRender()
{
    if (this->cfg.antiAliasing.type == noneAA)
    {
        return;
    }

    glDisable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, wsize.x, wsize.y);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glUseProgram(this->cfg.shadersList.postProcessingShader->programm);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, this->glValues.offscreenTexture);

    ivec2 pixels = getCountOfPixel(this->cfg.antiAliasing.value);
    glUniform2i(this->shaderCache.postProcessingShaderAntiAliasingPixels, pixels.x, pixels.y);

    glBindVertexArray(this->quad->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->quad->triangleCount);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDeleteFramebuffers(1, &this->glValues.offscreenBuffer);
    glDeleteTextures(1, &this->glValues.offscreenTexture);
    glDeleteRenderbuffers(1, &this->glValues.rbo);
}

void RenderManager::render(Model *m, glm::fvec3 position, glm::fvec3 turning)
{

    mat4 model = glm::translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    model = rotate(model, turning.x, vec3(1, 0, 0));
    model = rotate(model, turning.y, vec3(0, 1, 0));
    model = rotate(model, turning.z, vec3(0, 0, 1));

    glm::mat4 MVP = this->projection * this->view * model;

    glUniform1i(this->shaderCache.mainShaderTexture1Pos, 0);
    glUniformMatrix4fv(this->shaderCache.mainShaderMVPpos, 1, GL_FALSE, &MVP[0][0]);

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
