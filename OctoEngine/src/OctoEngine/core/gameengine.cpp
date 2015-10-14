#include "gameengine.h"
#include "game.h"
#include "gameobject.h"
#include "components/camera.h"
#include "time.h"
#include "../resources/resourcemanager.h"
#include "../graphics/shader.h"
#include "../graphics/mesh.h"
#include "../graphics/texture.h"
#include "../graphics/cubemap.h"
#include "../graphics/material.h"
#include "../input/input.h"
#include <iostream>
#include <string>


namespace octo
{
	namespace core
	{
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
			resources::ResourceManager::registerLoader<graphics::Shader>(octo::graphics::Shader::load);
			resources::ResourceManager::registerLoader<graphics::Mesh>(resources::loadMesh);
			resources::ResourceManager::registerLoader<graphics::Texture>(octo::graphics::Texture::load);
			resources::ResourceManager::registerLoader<graphics::CubeMap>(octo::graphics::CubeMap::load);
			resources::ResourceManager::registerLoader<graphics::Material>(octo::graphics::Material::load);

			//By default cull back faces
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			// By default enable depth testing
			glEnable(GL_DEPTH_TEST);	// Depth test enabled by default
			glDepthMask(GL_TRUE);

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
				//m_Window->clear();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

				// Make sure too long frames (maybe debugging ?) still behave properly
				if (oneSecond >= 1)
				{
					oneSecond = oneSecond - 1;
					std::cout << frameCount << " fps" << std::endl;
					frameCount = 0;
				}

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
		int GameEngine::getWindowWidth() const
		{
			return m_Window->getWidth();
		}

		int GameEngine::getWindowHeight() const
		{
			return m_Window->getHeight();
		}

		void GameEngine::setClearColor(glm::vec3& color)
		{
			m_Window->setClearColor(color);
		}

		void GameEngine::AddGameObject(GameObject* const gameObject)
		{
			m_RootGameObject->addChild(gameObject);
		}

		//void GameEngine::AddCamera(Camera * camera)
		//{
		//	std::hash<std::string> stringHash;
		//	// TODO add camera here
		//}

		void GameEngine::setMainCamera(Camera* mainCamera)
		{
			m_MainCamera = mainCamera;
		}

		Camera& GameEngine::getMainCamera()
		{
			//// If no camera is tagged MainCamera
			//Camera* mainCamera = m_Cameras[OCTO_MAIN_CAMERA_TAG];
			//OCTO_ASSERT((mainCamera == nullptr), "There is no Camera component tagged \'MainCamera\'");
			//return *mainCamera;

			return *m_MainCamera;
		}
	}
}
