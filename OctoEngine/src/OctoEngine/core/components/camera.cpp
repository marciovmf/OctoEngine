#include "camera.h"
#include "../gameobject.h"
#include "../transform.h"
#include "../octoengine.h"
#include <iostream>
#include "../gameengine.h"

namespace octo {
	namespace core {

		Camera::Camera() :
			Component()
		{
			setCameraFrustum(0.1f, 1000.0f, 16 / 9, 4.5f);
		}

		Camera::Camera(float near, float far, float ratio, float fov) :
			Component()
		{
			setCameraFrustum(near, far, ratio, fov);
		}

		Camera::~Camera()
		{
		}

		const glm::mat4& Camera::getViewMatrix()
		{
			Transform& t = gameObject->getTransform();

			// Does not recalculate the matrix if no changes were made on the transform
			if (!t.hasChanged())
				return m_ViewMatrix;

			// Update the matrix
			t.getTransformationMatrix();

			glm::vec3 pos = t.getPosition();
			glm::vec3 dir = t.forward();

			print("Position");
			octo::print(pos);
			print("forward");
			octo::print(dir);

			m_ViewMatrix =   glm::lookAt(pos, dir, glm::vec3(0, 1, 0));
			return m_ViewMatrix;

		}

		void Camera::setCameraFrustum(float near, float far, float ratio, float fov)
		{
			m_Near = near;
			m_Far = far;
			m_FOV = fov;
			m_AspectRatio = ratio;

			m_ProjectionMatrix =
				glm::perspective(m_FOV, m_AspectRatio, m_Near, m_Far);
		}
	}
}