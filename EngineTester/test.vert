#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
//layout (location = 2) in vec2 vTextCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


out vec4 vertexColor;
//out vec2 textCoord;


void main()
{

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition,1.0);
	vertexColor = vec4(vPosition, 1.0f);
	//textCoord = vTextCoord;

	//gl_Position  =  vec4(vPosition,1.0);
}
