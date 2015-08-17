#include "gameobject.h"
#include "components/component.h"
#include <algorithm>

#define DEFAULT_GAME_OBJECT_NAME "GameObject"

namespace octo
{
	namespace core {

		GameObject::GameObject()
		{
			m_Children = new std::vector<GameObject*>();
			m_Components = new std::vector<Component*>();
			m_Name = new std::string(DEFAULT_GAME_OBJECT_NAME);
			m_Trasnform = new Transform();
		}

		GameObject::~GameObject()
		{
			delete m_Children;
			delete m_Name;
		}

		const std::string& GameObject::getName() const
		{
			return *m_Name;
		}

		void GameObject::setName(std::string* name)
		{
			delete m_Name;
			m_Name = name;
		}

		void GameObject::addChild(GameObject* child)
		{
			m_Children->push_back(child);
			
			// Child transformations depends on this object transformations
			child->m_Trasnform->setParent(this->m_Trasnform);
		}

		void GameObject::removeChild(GameObject* child)
		{
			auto iter = m_Children->erase(
				std::remove(m_Children->begin(), m_Children->end(), child),
				m_Children->end()
				);

			// Child transformations no longer depends on this object transformations
			if (iter != m_Children->end())
			{
				child->m_Trasnform->setParent(nullptr);
			}
		}

		// add component
		void GameObject::addComponent(Component* component)
		{
			m_Components->push_back(component);
			component->setGameObject(this);
		}

		// remove component
		void GameObject::removeComponent(Component* component)
		{
			auto iter = m_Components->erase(
				std::remove(m_Components->begin(), m_Components->end(), component),
				m_Components->end()
				);

			//if we successfully removed the component,
			// remove its reference to this game object
			if (iter != m_Components->end())
				component->setGameObject(nullptr);
		}

		// Updates this game object
		void GameObject::update()
		{

			// Update all child game objects
			for (GameObject* gameObject : *m_Children)
			{
				gameObject->update();
			}

			// Update all comonents
			for (Component* component : *m_Components)
			{
				component->update();
			}

			// Update the transform
			m_Trasnform->update();
		}

		void GameObject::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
		{
			// Render all comonents
			for (Component* component : *m_Components)
			{
				component->render(projectionMatrix, viewMatrix);
			}
		}
	}
}