#pragma once
#include <OctoEngine/core/components/camera.h>
#include <OctoEngine/core/gameobject.h>
#include <OctoEngine/core/transform.h>
#include <OctoEngine/core/time.h>
#include <OctoEngine/input/input.h>


class TestCamera : public octo::core::Camera
{
public:

	TestCamera(float near, float far, float ratio, float fov) : octo::core::Camera(near, far, ratio, fov)
	{
	}

	~TestCamera()
	{
	}

	void update() override
	{
		octo::core::Transform& t = this->gameObject->getTransform();
		double deltaTime = octo::core::Time::getInstance().getDeltaTime();

		float step = (float)(5.0f * deltaTime);

		if (octo::input::Input::getKey(KEY_W))
			t.translate(glm::normalize(t.forward()) * step);
		else if (octo::input::Input::getKey(KEY_S))
			t.translate(glm::normalize(t.forward()) * -step);
		if (octo::input::Input::getKey(KEY_A))
			t.translate(glm::normalize(t.right()) * step);
		else if (octo::input::Input::getKey(KEY_D))
			t.translate(glm::normalize(t.right()) * -step);
		else if (octo::input::Input::getKey(KEY_Q))
			t.rotate(glm::vec3(0, 2 * deltaTime, 0));
		else if (octo::input::Input::getKey(KEY_E))
			t.rotate(glm::vec3(0, -2 * deltaTime, 0));



	}
};

