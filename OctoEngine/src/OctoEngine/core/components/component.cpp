#include "component.h"
#include "../gameobject.h"
#include <iostream>

namespace octo
{
	namespace core {

		Component::Component() : gameObject(nullptr), m_Enabled(true)
		{
		}

		Component::~Component()
		{
			destroy();
		}

		void Component::setEnabled(bool state)
		{
			m_Enabled = state;
		}

		void Component::setGameObject(GameObject* hostGameObject)
		{
			gameObject = hostGameObject;
		}

		void Component::start()
		{
		}

		void Component::update()
		{

		}

		void Component::render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
		{
		}

		void Component::destroy()
		{
			std::string name = gameObject->getName();
			std::cout << "Destroying component @" << name << std::endl;
		}

		GameObject& Component::getGameObject() const
		{
			return getGameObject;
		}
	
	
	}
}