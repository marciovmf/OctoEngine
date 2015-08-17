#include "component.h"

namespace octo
{
	namespace core {

		Component::Component() : gameObject(nullptr)
		{
		}

		Component::~Component()
		{
			destroy();
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

		void Component::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
		{

		}

		void Component::destroy()
		{

		}
	}
}