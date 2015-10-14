<SHADER>
<CULL>back</CULL>
 <ZWRITE>on</ZWRITE>
 <ZTEST>less</ZTEST>
<VERTEX>
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 vTextCoord;


out vec3 textCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(vPosition,1.0);
		
	// fix the image because soil loads it flipped verticaly
	textCoord = vPosition;

}
 </VERTEX>
 <FRAGMENT>

#version 330 core

in vec3 textCoord;
out vec4 color;

uniform samplerCube skyboxCubemap;

void main()
{
	color = texture(skyboxCubemap, textCoord);
}

 </FRAGMENT>
</SHADER>