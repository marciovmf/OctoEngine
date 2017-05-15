#pragma once

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

namespace octo
{
	namespace core
	{
		class GameObject;

		class Component
		{
		protected:
			GameObject* gameObject;
			bool m_Enabled;
		public:
			Component();
			virtual ~Component();

			void setGameObject(GameObject* hostGameObject);

			// lifecycle methods
			virtual void start();
			virtual void update();
			virtual void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			virtual void destroy();

			void setEnabled(bool state);

			inline bool isEnabled()
			{
				return m_Enabled;
			}

			GameObject& getGameObject() const;
		};
	}
}
