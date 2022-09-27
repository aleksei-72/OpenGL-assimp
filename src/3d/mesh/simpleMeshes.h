#ifndef SIMPLE_MESHES_H
#define SIMPLE_MESHES_H

#include <GL/glew.h>
#include <src/3d/mesh/mesh.h>

#include <vector>

std::vector<Vertex> generateCube(float scale);
std::vector<Vertex> generatePlain(float scale);
std::vector<Vertex> toVector(float *buffer, unsigned int bufferSize, float scale);

#endif // SIMPLE_MESHES_H
