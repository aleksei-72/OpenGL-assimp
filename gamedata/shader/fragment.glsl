#version 330

in vec2 ftexcoord;
in vec3 fposition;

out vec4 FragColor;

uniform sampler2D texture_1;

void main()
{
	vec4 color = texture(texture_1, ftexcoord.st);
	
	FragColor = vec4(color);
}
