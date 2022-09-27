#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/3d/mesh/Mesh.h>

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices)
{

    Vertex *buffer = new Vertex[vertices.size()];


    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        buffer[i] = vertices[i];
    }

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), buffer, GL_STATIC_DRAW);


    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
    glBindVertexArray(0); // unbind VAO

    triangleCount = vertices.size();
}
