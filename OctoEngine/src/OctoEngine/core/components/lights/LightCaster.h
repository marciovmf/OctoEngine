#pragma once
#include "../component.h"

namespace octo
{
	namespace core
	{
		class LightCaster : public octo::core::Component
		{
		protected:
			glm::vec3 m_Color;
			float m_Intensity;

		public:
			LightCaster();
			virtual ~LightCaster();
			void setColor(glm::vec3& color);
			void setColor(float r, float g, float b);
			void setIntensity(float intensity);
			const glm::vec3& getColor() const;
			float getIntensity() const;
		};
	}
}
