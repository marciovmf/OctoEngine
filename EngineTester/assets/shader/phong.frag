#version 330 core

in vec2 textCoord;
in vec3 normal;
out vec4 color;

// light test
in vec3 lightColor;
in vec3 fragPos;
in vec3 lightPos;

uniform sampler2D diffuse;
uniform float ambientIntensity;
uniform vec3 ambientLight;


void main()
{
	
	// Ambient light
	vec3 ambientComponent = (ambientLight * ambientIntensity);

	// Diffuse light
	vec3 norm = normalize(normal);
	vec3 lightDir =  normalize( lightPos - fragPos);
	float angle =  max(dot(norm, lightDir),0.0);
	vec3 diffuseComponent = angle * lightColor;
	
	vec3 result = (ambientComponent + diffuseComponent);
	
	color = vec4(result, 1.0) * texture(diffuse, textCoord);
	
}
