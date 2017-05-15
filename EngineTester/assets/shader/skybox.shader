<SHADER>
 <CULL>back</CULL>
 <ZWRITE>on</ZWRITE>
 <ZTEST>lequal</ZTEST>
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
	mat4 untranslatedViewMatrix = mat4(mat3(viewMatrix));  // Remove translation from view matrix
	vec4 pos = projectionMatrix * untranslatedViewMatrix * vec4(vPosition,1.0);
	gl_Position = pos.xyww;
	textCoord = vec3(-vPosition.x, vPosition.yz); // Because texture is loaded flipped
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