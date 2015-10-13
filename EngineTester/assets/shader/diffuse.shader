<SHADER>
 <VERTEX>
 #version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 vTextCoord;


out vec2 textCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragPos;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition,1.0);
		
	// fix the image because soil loads it flipped verticaly
	textCoord = vTextCoord;//vec2(vTextCoord.x, textCoord.y);

}
 </VERTEX>
 <FRAGMENT>
 
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
 
 </FRAGMENT>
 <CULL>BACK</CULL>
 <ZWRITE>OFF</ZWRITE>
 <ZTEST>LESS</ZTEST>
</SHADER>