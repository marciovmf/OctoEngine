#include "gameobject.h"
#include "components/component.h"
#include "components/camera.h"
#include <algorithm>
#include <iostream>

#define DEFAULT_GAME_OBJECT_NAME "GameObject"

namespace octo
{
	namespace core {

		GameObject::GameObject() : m_Enabled(true)
		{
			m_Children = new std::vector<GameObject*>();
			m_Components = new std::vector<Component*>();
			m_Name = new std::string(DEFAULT_GAME_OBJECT_NAME);
			m_Trasnform = new Transform();
		}

		GameObject::~GameObject()
		{
			for (Component* i : *m_Components)
			{
				delete i;
			}

			for (GameObject* i : *m_Children)
			{
				delete i;
			}
			
			std::cout << "Destroying game object: " << *m_Name << std::endl;

			delete m_Children;
			delete m_Components;
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

		// Initialize all components
		void GameObject::initializeComponents()
		{
			for (GameObject* i : *m_Children)
			{
				i->initializeComponents();
			}

			for (Component* i : *m_Components)
			{
				i->start();
			}

			std::cout << "Game object " << m_Name->c_str() << " initialized." << std::endl;
		}

		// Updates this game object
		void GameObject::update()
		{
			// Update the transform
			m_Trasnform->update();

			// Update all active child game objects
			for (GameObject* gameObject : *m_Children)
			{
				if (gameObject->m_Enabled)
					gameObject->update();
			}

			// Update all active comonents
			for (Component* component : *m_Components)
			{
				if (component->isEnabled())
					component->update();
			}


		}

		void GameObject::setEnabled(bool state){
			m_Enabled = state;
		}

		//void GameObject::render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
		void GameObject::render(Camera& camera)
		{

			// Render child objects
			for (GameObject* child : *m_Children)
			{
				if (child->m_Enabled)
				{
					child->render(camera);
				}
			}

			// Render all components
			for (Component* component : *m_Components){
				if (component->isEnabled()){
					component->render(camera.getProjectionMatrix(), camera.getViewMatrix());
				}
			}
		}
	}
}