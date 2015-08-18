#include "TestGame.h"
#include <iostream>
#include <vector>
#include <OctoEngine/core/gameengine.h>
#include <OctoEngine/core/game.h>
#include <OctoEngine/core/transform.h>
#include <OctoEngine/graphics/shader.h>
#include <OctoEngine/graphics/mesh.h>
#include <OctoEngine/graphics/vertex.h>
#include <OctoEngine/core/gameobject.h>
#include <OctoEngine/core/components/meshrenderer.h>
#include <OctoEngine/core/components/camera.h>

#include <glm/vec2.hpp>
#include <glm/gtc/constants.hpp>

std::vector<octo::graphics::Vertex> vertices{
	// front
	octo::graphics::Vertex(glm::vec3(-1.0, -1.0, 1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(1.0, -1.0, 1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(-1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0)),
	// back
	octo::graphics::Vertex(glm::vec3(-1.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(1.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(1.0, 1.0, -1.0), glm::vec3(1.0, 1.0, 1.0)),
	octo::graphics::Vertex(glm::vec3(-1.0, 1.0, -1.0), glm::vec3(1.0, 1.0, 1.0))
};


std::vector<GLuint> indices{
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	3, 2, 6,
	6, 7, 3,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// left
	4, 0, 3,
	3, 7, 4,
	// right
	1, 5, 6,
	6, 2, 1,
};

TestGame::TestGame()
{
}

TestGame::~TestGame()
{
}

void TestGame::OnStart()
{
	std::cout << "Game Started" << std::endl;

	m_Shader = new octo::graphics::Shader("test.vert", "test.frag");

	// Set up Projection
	//m_ProjectionMatrix =
	//	glm::perspective(glm::radians(45.0f),
	//	(float)(engine->getWindowWidth() / engine->getWindowHeight()),
	//	0.1f, 1000.0f);

	// Create the meshe
	m_Mesh = new octo::graphics::Mesh(vertices, indices);

	// "Root" game object
	m_GameObject1 = new octo::core::GameObject();
	m_GameObject1->setName(new std::string("Root"));
	m_GameObject1->getTransform().setPosition(glm::vec3(0, 0, 0));
	m_GameObject1->getTransform().setScale(glm::vec3(0.2, 0.2, 0.2));
	m_meshRenderer1 = new octo::core::MeshRenderer(m_Shader, m_Mesh);
	m_GameObject1->addComponent(m_meshRenderer1);

	// Child game object 1
	m_GameObject2 = new octo::core::GameObject();
	m_GameObject2->setName(new std::string("Child1"));
	m_GameObject2->getTransform().setPosition(glm::vec3(0.5, 0.0, -5.0));
	m_meshRenderer2 = new octo::core::MeshRenderer(m_Shader, m_Mesh);
	m_GameObject2->addComponent(m_meshRenderer2);

	// Child game object 2
	m_GameObject3 = new octo::core::GameObject();
	m_GameObject3->setName(new std::string("Child2"));
	m_GameObject3->getTransform().translate(glm::vec3(0.0, 1.5, 5.0));
	m_GameObject3->getTransform().rotate(glm::vec3(90, 0.5, 90));
	m_meshRenderer3 = new octo::core::MeshRenderer(m_Shader, m_Mesh);
	m_GameObject3->addComponent(m_meshRenderer3);

	// Parent the child objects to the Root object
	m_GameObject1->addChild(m_GameObject2);
	m_GameObject1->addChild(m_GameObject3);

	// Create the CAMERA
	m_CameraGameObject = new octo::core::GameObject();
	m_CameraGameObject->setName(new std::string("Camera"));
	m_Camera = new octo::core::Camera(0.1f, 1000.0f, (float) (engine->getWindowWidth() / engine->getWindowHeight()), 45.0f);
	m_CameraGameObject->addComponent(m_Camera);

	// Place the camera
	m_CameraGameObject->getTransform().translate(glm::vec3(0.0f, 0.0f, -190));

	engine->setClearColor(glm::vec3(0.4, 0.4, 0.4));
	engine->AddGameObject(m_CameraGameObject);
	engine->AddGameObject(m_GameObject1);
	engine->setMainCamera(m_Camera);
}

double frameTime = 0;
void TestGame::OnUpdate()
{

	double startTime = glfwGetTime();
	
	float t = (float)sin(glfwGetTime());
	float f = t;
	// make some transformations on the game objects
	m_GameObject1->getTransform().setPosition(glm::vec3(0, t, 0));
	m_GameObject1->getTransform().rotate(glm::vec3(glm::radians(t / 8), -glm::radians(t / 2), -glm::radians(1 * frameTime)));
	m_GameObject2->getTransform().rotate(glm::vec3(0, 0, glm::radians(t / 2)));

	m_GameObject3->getTransform().setScale(glm::vec3(f, f, f));

	double frameTime = (glfwGetTime() - startTime);

	//std::cout << frameTime << std::endl;
}

void TestGame::OnFinish()
{
	delete m_GameObject1;
	delete m_GameObject2;
	delete m_GameObject3;
	delete m_CameraGameObject;

	delete m_Mesh;
	delete m_Shader;
	delete m_Camera;

	delete m_meshRenderer1;
	delete m_meshRenderer2;
	delete m_meshRenderer3;

	std::cout << "Game Finished!" << std::endl;
}