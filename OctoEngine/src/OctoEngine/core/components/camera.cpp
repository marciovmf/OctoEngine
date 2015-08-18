#include "camera.h"
#include "../gameobject.h"
#include "../transform.h"
#include <iostream>

namespace octo {
	namespace core {

		Camera::Camera() :
			Component()
		{
			setCameraFrustum(0.1f, 1000.0f, 16/9, 4.5f);
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


			mat4 transformations; // Identity

			// Translation
			transformations = glm::translate(transformations, t.getPosition());

			// Rotation
			transformations *= mat4_cast(glm::inverse(t.getRotation()));

			// Scale
			transformations = glm::scale(transformations, t.getScale());

			// transform the camera viewProjectionMatrix according to the camera position/rotation
			m_ViewMatrix = transformations;

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