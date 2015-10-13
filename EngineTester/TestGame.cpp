#include "TestGame.h"
#include <iostream>
#include <vector>
#include <OctoEngine/core/gameengine.h>
#include <OctoEngine/core/game.h>
#include <OctoEngine/core/transform.h>
#include <OctoEngine/graphics/mesh.h>
#include <OctoEngine/graphics/vertex.h>
#include <OctoEngine/core/gameobject.h>
#include <OctoEngine/core/components/meshrenderer.h>

#include "TestComponent.h"
#include "TestCamera.h"
#include <OctoEngine/resources/resourcemanager.h>
#include <OctoEngine/graphics/material.h>
#include <OctoEngine/graphics/rendersettings.h>

std::vector<octo::graphics::Vertex> vertices{
	// Vertex , Normal, UV
	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),

	octo::graphics::Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),

	octo::graphics::Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),

	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),

	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),

	octo::graphics::Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	octo::graphics::Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
	octo::graphics::Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f)

};

std::vector<octo::graphics::Vertex> planeVertices{
	// front
	octo::graphics::Vertex(0.5, 0.0, 0.5, 0.0f, 1.0f, 0.0f, 1.0, 0.0),
	octo::graphics::Vertex(0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0f, 1.0, 1.0),
	octo::graphics::Vertex(-0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0f, 0.0, 1.0),
	octo::graphics::Vertex(-0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0f, 0.0, 1.0),
	octo::graphics::Vertex(-0.5, 0.0, 0.5, 0.0f, 1.0f, 0.0f, 0.0, 0.0),
	octo::graphics::Vertex(0.5, 0.0, 0.5, 0.0f, 1.0f, 0.0f, 1.0, 0.0),
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

	std::shared_ptr<octo::graphics::Material> MaterialPtr =
		octo::resources::ResourceManager::get<octo::graphics::Material>("assets/material/phong.mat");
	std::shared_ptr<octo::graphics::Material> GroundMaterialPtr =
		octo::resources::ResourceManager::get<octo::graphics::Material>("assets/material/checkers.mat");


	// Resources: Shander and Mesh
	m_boxMesh = new octo::graphics::Mesh(vertices);
	m_planeMesh = new octo::graphics::Mesh(planeVertices);

	// "Ground" game object
	octo::core::GameObject* m_Ground = new octo::core::GameObject();
	m_Ground->setName(new std::string("Ground"));
	m_Ground->addComponent(new octo::core::MeshRenderer(GroundMaterialPtr, m_planeMesh));
	m_Ground->getTransform().scale(glm::vec3(10.0f, 10.0f, 10.0f));
	m_Ground->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	// "BOX" game object
	octo::core::GameObject* m_Box = new octo::core::GameObject();
	m_Box->setName(new std::string("Box"));
	m_Box->addComponent(new octo::core::MeshRenderer(MaterialPtr, m_boxMesh));
	//m_Box->getTransform().scale(glm::vec3(10.0f, 10.0f, 10.0f));
	m_Box->addComponent(new TestComponent());

	octo::core::GameObject* m_BoxChild1 = new octo::core::GameObject();
	m_BoxChild1->setName(new std::string("Child1"));
	m_BoxChild1->addComponent(new octo::core::MeshRenderer(MaterialPtr, m_boxMesh));
	//m_Box->getTransform().scale(glm::vec3(10.0f, 10.0f, 10.0f));
	m_BoxChild1->getTransform().translate(glm::vec3(4.0f, -0.4f, 4.0f));

	octo::core::GameObject* m_BoxChild2 = new octo::core::GameObject();
	m_BoxChild2->setName(new std::string("Child2"));
	m_BoxChild2->addComponent(new octo::core::MeshRenderer(MaterialPtr, m_boxMesh));
	//m_Box->getTransform().scale(glm::vec3(10.0f, 10.0f, 10.0f));
	m_BoxChild2->getTransform().setPosition(glm::vec3(3.0f, 2.0f, -1.0f));

	m_Box->addChild(m_BoxChild1);
	m_Box->addChild(m_BoxChild2);


	// Create the CAMERA
	octo::core::GameObject* m_CameraGameObject = new octo::core::GameObject();
	m_CameraGameObject->setName(new std::string("Camera"));
	//auto m_Camera = new octo::core::Camera(0.1f, 1000.0f, (float)(engine->getWindowWidth() / engine->getWindowHeight()), 35.0f);
	auto m_Camera = new TestCamera(0.01f, 1000.0f, (float)(engine->getWindowWidth() / engine->getWindowHeight()), 45.0f);
	m_CameraGameObject->addComponent(m_Camera);

	// Place the camera
	m_CameraGameObject->getTransform().lookAt(glm::vec3(0, 0, 0));
	m_CameraGameObject->getTransform().translate(glm::vec3(0.0f, 1.0f, -5.0f));
	// Add the objets to the engine
	engine->setClearColor(glm::vec3(0.4, 0.4, 0.4));
	engine->setMainCamera(m_Camera);
	engine->AddGameObject(m_Ground);
	engine->AddGameObject(m_Box);
	engine->AddGameObject(m_CameraGameObject);
}


//void TestGame::OnUpdate()
//{
//}

void TestGame::OnFinish()
{
	delete m_boxMesh;
	delete m_planeMesh;
	std::cout << "Game Finished!" << std::endl;
}
