#include "component.h"

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

		void Component::setGameObject(GameObject* gameObject)
		{
			this->gameObject = gameObject;
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

		}
	
	
	}
}