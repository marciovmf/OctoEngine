<SHADER>
 <CULL>BACK</CULL>
 <ZWRITE>OFF</ZWRITE>
 <ZTEST>LESS</ZTEST>
 <VERTEX>
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTextCoord;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 textCoord;

// light test
out vec3 lightColor;
out vec3 fragPos;
out vec3 lightPos;
out vec3 normal;

//out vec3 FragPos;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition,1.0);
		
	// fix the image because soil loads it flipped verticaly
	textCoord = vTextCoord;//vec2(vTextCoord.x, textCoord.y);
	
	normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
	
	// light test
	lightColor = vec3(1);
	lightPos = vec3(0, 1, -1);	
	fragPos =  vec3( modelMatrix * vec4(vPosition,1.0));

}

 </VERTEX>
 <FRAGMENT>
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
	
}</FRAGMENT>
</SHADER>