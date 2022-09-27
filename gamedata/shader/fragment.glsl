#version 330

in vec2 ftexcoord;
in vec3 fposition;

out vec4 FragColor;

uniform sampler2D mainTexture;

void main()
{
	vec4 color = texture(mainTexture, ftexcoord.st);
	
	FragColor = vec4(color);
}
