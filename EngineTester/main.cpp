
#define GLM_FORCE_RADIANS 1

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <OctoEngine/window.h>
#include <OctoEngine/graphics/shader.h>
#include <OctoEngine/resources/resource.h>
#include <OctoEngine/resources/resourcemanager.h>
#include <OctoEngine/resources/textureloader.h>
#include <OctoEngine/resources/texture.h>
#include <OctoEngine/graphics/vertex.h>
#include <OctoEngine/graphics/mesh.h>

#include <regex>

using namespace octo;
using namespace resources;

int main(int argc, char** argv)
{
	const int VIEWPORT_WIDTH = 640;
	const int VIEWPORT_HEIGHT = 480;

	octo::core::Window gameWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "OctoEngine");
	octo::graphics::Shader* shader = new octo::graphics::Shader("test.vert", "test.frag");

	graphics::Vertex vertexData[]{
		// front
		graphics::Vertex(glm::vec3(1.0, -1.0, 1.0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // 0
			graphics::Vertex(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // 1
			graphics::Vertex(glm::vec3(-1.0, -1.0, 1.0), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // 2
			graphics::Vertex(glm::vec3(-1.0, 1.0, 1.0), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // 3
			graphics::Vertex(glm::vec3(1.0, 1.0, -1.0), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // 4
			graphics::Vertex(glm::vec3(-1.0, 1.0, -1.0), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),// 5
			graphics::Vertex(glm::vec3(1.0, -1.0, -1.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // 6
			graphics::Vertex(glm::vec3(-1.0, -1.0, -1.0), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // 7
	};

	GLuint indices[]{
		1, 3, 2, 2, 0, 1,
			3, 1, 4, 4, 5, 3,
			6, 7, 5, 5, 4, 6,
			7, 6, 0, 0, 2, 7,
			7, 2, 3, 3, 5, 7,
			0, 6, 4, 4, 1, 0,
	};

	graphics::Mesh* mesh = new graphics::Mesh(vertexData,
		sizeof(vertexData) / sizeof(graphics::Vertex),
		indices,
		sizeof(indices) / sizeof(GLuint));

	// Set up Projection
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)(VIEWPORT_WIDTH / VIEWPORT_HEIGHT), 0.1f, 100.0f);

	// Set up view transformations
	glm::mat4 viewMatrix;
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.2f, -8.0f));
	//viewMatrix = glm::rotate(viewMatrix, -15.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	// Set up Model transformations
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));

	glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	gameWindow.setClearColor(glm::vec3(0.3f, 0.3f, 0.3f));
	while (!gameWindow.shouldClose())
	{
		gameWindow.clear();

		modelMatrix = glm::rotate(modelMatrix, 0.001f * (float)sin(glfwGetTime()) * 2, glm::vec3(1.0f, -1.0f, 0));
		mesh->render(*shader, modelMatrix, viewMatrix, projectionMatrix);
		gameWindow.update();
	}

	delete shader;
	return 0;
}