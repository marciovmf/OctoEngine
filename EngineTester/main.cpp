#include <iostream>
#include <glm/vec3.hpp>

#include <OctoEngine/window.h>
#include <OctoEngine/shader.h>
#include <OctoEngine/buffer.h>
#include <OctoEngine/vertexarray.h>

#define GLEW_STATIC

using namespace octo;

int main(int argc, char** argv)
{

	const int VIEWPORT_WIDTH = 640;
	const int VIEWPORT_HEIGHT = 480;

	octo::core::Window gameWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "OctoEngine");
	octo::graphics::Shader* shader = new octo::graphics::Shader("test.vert", "test.frag");

	// Sprite 1
	GLfloat  vertices[]{-0.5, -0.5, 0.0, -0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, -0.5, 0.0};
	GLfloat colors[] {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0	};
	octo::graphics::VertexArray* sprite1 = new octo::graphics::VertexArray();
	octo::graphics::Buffer* vertexBuffer = new octo::graphics::Buffer(vertices, 3 * 4, 3);
	octo::graphics::Buffer* colorBuffer = new octo::graphics::Buffer(colors, 3 * 4, 3);
	sprite1->addBuffer(vertexBuffer, 0);
	sprite1->addBuffer(colorBuffer, 1);

	// Sprite 2
	GLfloat  vertices2[]{-1.0, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0};
	GLfloat colors2[]  {  1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
	octo::graphics::VertexArray* sprite2 = new octo::graphics::VertexArray();
	octo::graphics::Buffer* vertexBuffer2 = new octo::graphics::Buffer(vertices2, 3 * 4, 3);
	octo::graphics::Buffer* colorBuffer2 = new octo::graphics::Buffer(colors2, 3 * 4, 3);
	sprite2->addBuffer(vertexBuffer2, 0);
	sprite2->addBuffer(colorBuffer2, 1);

	// indices
	GLushort indices[] { 0, 1, 2, 2, 3, 0 };
	graphics::Buffer* indexBuffer = new graphics::Buffer(indices, 6, 1, graphics::Buffer::INDEX_DATA);



	glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);



	while (!gameWindow.shouldClose())
	{
		gameWindow.clear();
		shader->Bind();

		sprite1->bind();
		indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);
		indexBuffer->unbind();
		sprite1->unbind();

		sprite2->bind();
		indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);
		indexBuffer->unbind();
		sprite2->unbind();

		shader->Unbind();
		gameWindow.update();
	}



	delete shader;
	return 0;
}