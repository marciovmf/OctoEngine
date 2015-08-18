#pragma once
#include <OctoEngine\core\components\component.h>
#include <OctoEngine\core\transform.h>
#include <OctoEngine\core\gameobject.h>

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
		transform.setPosition(glm::vec3(0, 0, 0));
		transform.setScale(glm::vec3(0.2, 0.2, 0.2));

		std::vector<octo::core::GameObject*> children = gameObject->getChildren();
		child1 = children[0];
		child2 = children[1];
	}

	void update() override
	{
		octo::core::Transform& transform = this->gameObject->getTransform();
		transform.rotate(glm::vec3(glm::radians(0.05), -glm::radians(1.0), -glm::radians(0.5)));
		
		//child1->getTransform().rotate(glm::vec3(0, 0, glm::radians(5.0)));
		child2->getTransform().rotate(glm::vec3(glm::radians(2.0), 0, glm::radians(-1.0)));
	}

	void destroy() override
	{
		std::cout << "Finalizando TestComponent" << std::endl;
	}
};

