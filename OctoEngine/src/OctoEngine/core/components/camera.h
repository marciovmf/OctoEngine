#pragma once

#include "component.h"


namespace octo
{
	namespace core
	{
		class Camera : public Component
		{
		private:
			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;

			float m_Near;
			float m_Far;
			float m_FOV;
			float m_AspectRatio;
		public:
			Camera();
			Camera(float near, float far, float ratio, float fov);
			virtual ~Camera();
			void setCameraFrustum(float near, float far, float ratio, float fov);
			const glm::mat4& getViewMatrix();

			inline const glm::mat4& getProjectionMatrix()
			{
				return m_ProjectionMatrix;
			}
		};
	}
}
