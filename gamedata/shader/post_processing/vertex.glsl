#version 330
layout(location = 0) in vec4 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec3 vnormal;

out vec2 ftexcoord;


void main() {
    ftexcoord = vtexcoord;
    gl_Position = vposition;
}
