#include "game.h"
#include "gameengine.h"
#include "gameobject.h"
#include "components/camera.h"
#include <iostream>
#include <string>

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

		void GameEngine::run(int width, int height, std::string title, Game& game, int monitor)
		{
			// Give to the game a reference to this class
			game.setEngine(this);

			// Initialize the game window and the graphics system
			m_Window = new Window(width, height, title, monitor);
			// Setup viewport
			glViewport(0, 0, width, height);

			// Allows the game to make its own initializations
			game.OnStart();

			// Initialize all gameObjects created by the game
			m_RootGameObject->initializeComponents();

			// Run the main loop
			while (!m_Window->shouldClose())
			{
				m_Window->clear();
				game.OnUpdate();

				// Update all game objects and components
				m_RootGameObject->update();

				// Render all game objects
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
			}

			// Let the game do its own cleanup
			game.OnFinish();
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