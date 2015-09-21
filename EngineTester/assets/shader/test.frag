#version 330 core

in vec4 vertexColor;
in vec2 textCoord;
out vec4 color;

uniform vec3 meshColor;
uniform vec3 base_color;
uniform float ambient_intensity;
void main()
{
	/*
	for ( int i=0; i < MAX_DIFFUSE_TEXTURES; i++)
		color = mix (texture(TextureDiffuse[i], textCoord), color, i/2);
	
	color = color * vertexColor;
	*/

	//color = mix (vec4(meshColor,1.0) , vertexColor, 0.4) ;
	color = vec4(base_color,1.0) * ambient_intensity ;
}