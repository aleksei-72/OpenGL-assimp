#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <src/gl/texture.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

class Mesh
{
public:

    Mesh(std::vector <Vertex> vertices);
    std::vector <Texture*> diffuseTextures;

    GLuint vao, vbo;

    int triangleCount;
private:
};

#endif // MESH_H
