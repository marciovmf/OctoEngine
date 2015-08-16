#pragma once
#include "transform.h"
#include <vector>
#include <map>
#include <string>

namespace octo
{
	namespace core {

		class Component;

		class GameObject
		{
		private:
			Transform* m_Trasnform;
			std::string* m_Name;
			std::vector <GameObject* >* m_Children;
			std::vector<Component* >* m_Components;

		public:
			GameObject();
			~GameObject();

			inline Transform& getTransform() { return *m_Trasnform;  }
			const std::string& getName() const;
			void setName(std::string* name);

			void addChild(GameObject* child);
			void removeChild(GameObject* child);
			
			// add component
			void addComponent(Component* component);
			// remove component
			void removeComponent(Component* component);
			// get all children
			// get all components
			// get a specific child
			// get a specific component
			// get the number of components
			// get the number of children

			void update();
			void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
		};

	}
}