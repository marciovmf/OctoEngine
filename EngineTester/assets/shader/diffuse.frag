#version 330 core

in vec2 textCoord;
in vec3 FragPos; 
out vec4 color;

uniform sampler2D diffuse;

void main()
{

	vec3 ambientColor = vec3(1,1,1 );
	float ambientIntensity = 0.9f;
	
	vec4 ambientLight = vec4(ambientColor * ambientIntensity, 1.0);
	
	color = texture(diffuse, textCoord) * ambientLight;
}
