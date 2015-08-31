#include "game.h"
#include "gameengine.h"
#include "gameobject.h"
#include "components/camera.h"
#include <iostream>
#include <string>
#include "time.h"
#include "../resources/resourcemanager.h"
#include "../graphics/shader.h"
#include "../graphics/mesh.h"
#include "../graphics/texture.h"
#include "../graphics/material.h"
#include "../input/input.h"



namespace octo {

	namespace core {

		GameEngine::GameEngine()
			: m_Window(NULL), m_RootGameObject(new GameObject()), m_MainCamera(nullptr)
		{
			m_RootGameObject->setName(new std::string("__OCTO_SCENE_ROOT_OBJECT__"));
		}

		GameEngine::~GameEngine()
		{
			// clean up engine resources
			if (m_Window)
				delete m_Window;

			delete m_RootGameObject;
		}

		double oneSecond = 0;
		int frameCount = 0;
		void GameEngine::run(int width, int height, std::string title, Game& game, int monitor)
		{

			// Initialzie the resource manager and assign the default loaders
			resources::ResourceManager::initialize();			
			resources::ResourceManager::registerLoader<graphics::Shader>(resources::loadShader);
			resources::ResourceManager::registerLoader<graphics::Mesh>(resources::loadMesh);
			resources::ResourceManager::registerLoader<graphics::Texture>(resources::loadTexture);
			resources::ResourceManager::registerLoader<graphics::Material>(resources::loadMaterial);

			// Initialize the game window and the graphics system
			m_Window = new Window(width, height, title, monitor);

			// Initialize the Input system
			octo::input::Input::init(*m_Window);

			// Give to the game a reference to this class
			game.setEngine(this);

			// Setup viewport
			glViewport(0, 0, width, height);

			// Allows the game to make its own initializations
			game.OnStart();

			// Initialize all gameObjects created by the game
			m_RootGameObject->initializeComponents();

			// ----------------------------------
			// Run the main loop
			// ----------------------------------
			while (!m_Window->shouldClose())
			{
				// Update the game
				//game.OnUpdate();

				// Update all game objects and components
				m_RootGameObject->update();

				// Render all game objects
				m_Window->clear();
				if (m_MainCamera != nullptr)
				{
					m_RootGameObject->render(*m_MainCamera);
				}
				else
				{
					std::cout << "WARNING: No 'MainCamera' specified!" << std::endl;
				}

				// Update the window events and swap buffers
				m_Window->update();

				Time::getInstance().update();

				double deltaTime = Time::getInstance().getDeltaTime();

				// measure the number of frames per second
				oneSecond += deltaTime;
				frameCount++;

				if (oneSecond >= 1)
				{
					oneSecond = oneSecond - 1;
					std::cout << frameCount << " fps" << std::endl;
					frameCount = 0;
				}
				// --
			}

			// ----------------------------------
			// Cleanup
			// ----------------------------------
			// Let the game do its own cleanup
			game.OnFinish();
			resources::ResourceManager::Destroy();
			core::Time::destroy();
		}

		// Window Facade methods
		int GameEngine::getWindowWidth() const { return m_Window->getWidth(); }
		int GameEngine::getWindowHeight() const { return m_Window->getHeight(); }
		void GameEngine::setClearColor(glm::vec3& color)
		{
			m_Window->setClearColor(color);
		}

		void GameEngine::AddGameObject(GameObject* const gameObject)
		{
			m_RootGameObject->addChild(gameObject);
		}

		void GameEngine::setMainCamera(Camera* mainCamera)
		{
			m_MainCamera = mainCamera;
		}
	}
}