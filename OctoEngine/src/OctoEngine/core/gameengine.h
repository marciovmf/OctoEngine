#pragma once

#include "window.h"
#include <string>
#include <glm/vec3.hpp>
#include <map>
#include <string>

#define OCTO_MAIN_CAMERA_TAG "MainCamera"

namespace octo
{
	namespace core
	{
		class Game;
		class GameObject;
		class Camera;

		class GameEngine
		{
		private:
			GameObject* const m_RootGameObject;
			Window* m_Window;
			Camera* m_MainCamera;
		public:
			//

			// Core methods
			GameEngine();
			~GameEngine();
			void run(int width, int height, std::string title, Game& game, int monitor = -1);

			// Window facade methods

			int getWindowWidth() const;
			int getWindowHeight() const;
			void setClearColor(glm::vec3& color);

			void AddGameObject(GameObject* const gameObject);

			void setMainCamera(Camera* mainCamera);
			//inline Camera& getMainCamera() { return *m_MainCamera; }
			Camera& getMainCamera();
			void AddCamera(Camera* camera);
		};
	}
}
