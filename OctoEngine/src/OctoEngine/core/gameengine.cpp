#include "game.h"
#include "gameengine.h"
#include "gameobject.h"
#include "components/camera.h"
#include <iostream>
#include <string>
#include "time.h"

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
			// Give to the game a reference to this class
			game.setEngine(this);

			core::Time::initialize();

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

				// Start the frame time
				Time::setFrameStartTime();

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

				// End frame time
				Time::setFrameEndTime();

				double deltaTime = Time::getDeltaTime();
				//std::cout << deltaTime << std::endl;

				oneSecond += deltaTime;
				frameCount++;
				if (oneSecond >= 1)
				{
					// keep the exceeding time if any
					oneSecond = oneSecond - 1;
					std::cout << frameCount << std::endl;
					frameCount = 0;
				}
			}

			// Let the game do its own cleanup
			game.OnFinish();
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