#pragma once
#include <OctoEngine/core/components/component.h>
#include <OctoEngine/core/transform.h>
#include <OctoEngine/core/gameobject.h>
#include <OctoEngine/core/time.h>
#include <OctoEngine/input/input.h>
#include <iomanip>
class TestComponent :
	public octo::core::Component
{
private:
	octo::core::GameObject* child1;
	octo::core::GameObject* child2;
public:

	
	TestComponent() 
		: octo::core::Component()
	{
	}

	~TestComponent()
	{

	}

	void start() override
	{
		octo::core::Transform& transform = this->gameObject->getTransform();
		transform.setPosition(glm::vec3(0, 1, 0));
		transform.setScale(glm::vec3(0.2, 0.2, 0.2));

		std::vector<octo::core::GameObject*> children = gameObject->getChildren();
		child1 = children[0];
		child2 = children[1];
	}


	void update() override
	{
		double deltaTime = octo::core::Time::getInstance().getDeltaTime();
		octo::core::Transform& transform = this->gameObject->getTransform();
		transform.rotate(
			glm::vec3(0.0, 
			glm::radians(180.0) * deltaTime, 
			glm::radians(30.0) * deltaTime));
		
		child1->getTransform().rotate(glm::vec3(0, glm::radians(30.0)  * deltaTime, glm::radians(90.0)  * deltaTime));
		child2->getTransform().rotate(glm::vec3(
			0,
			glm::radians(90.0) * deltaTime,
			glm::radians(-360.0) * deltaTime));

	}

	void destroy() override
	{
		std::cout << "Finalizando TestComponent" << std::endl;
	}
};

