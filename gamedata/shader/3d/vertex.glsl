#version 330

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec3 vnormal;

uniform mat4 mvp;

out vec2 ftexcoord;
out vec3 fposition;

void main() 
{
	fposition = vposition;
    ftexcoord = vtexcoord;
	
    gl_Position = mvp * vec4(vposition, 1);
}
