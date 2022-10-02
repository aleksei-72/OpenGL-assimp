#version 330
uniform sampler2D texture_1;
uniform ivec2 aaPixels; 

in vec2 ftexcoord;

out vec4 FragColor;


vec3 FXAA_Filter(sampler2D tex, vec2 st, int stepX, int spetY)
{

	vec3 col = vec3(0, 0, 0);
	//Размер одного пикселя
	vec2 offset = 1.0 / textureSize(tex, 0);
	
	for(int i = -stepX/2 ; i < stepX/2; i++)
	{

		for(int j = -spetY/2; j < spetY/2; j++)
		{
			col += vec3(texture(tex, st.st + offset * vec2(i, j)));
		}

		
	}
	
	return col / (stepX * spetY);
}

void main()
{
	//vec3 color = vec3(texture(texture_1, ftexcoord.st));
	vec3 color = FXAA_Filter(texture_1, ftexcoord.st, aaPixels.x, aaPixels.y);
	
	FragColor = vec4(color, 1.0);
}
