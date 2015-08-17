#pragma once

#include <glm/glm.hpp>

namespace octo
{
	namespace core {

		class GameObject;

		class Component
		{
		protected:
			GameObject* gameObject;

		public:
			Component();
			virtual ~Component();

			void setGameObject(GameObject* gameObject);

			// lifecycle methods
			virtual void start();
			virtual void update();
			virtual void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
			virtual void destroy();
		};

	}
}