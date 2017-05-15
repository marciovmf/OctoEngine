#include "lightcaster.h"


namespace octo
{
	namespace core
	{
		LightCaster::LightCaster():
			Component(),
			m_Color(glm::vec3(1.0f, 1.0f, 1.0f)),
			m_Intensity(0.3f)
		{
		}

		void LightCaster::setColor(glm::vec3& color)
		{
			m_Color = color;
		}

		void LightCaster::setColor(float r, float g, float b)
		{
			m_Color.r = r;
			m_Color.g = g;
			m_Color.b = b;
		}


		void LightCaster::setIntensity(float intensity)
		{
			m_Intensity = intensity;
		}

		const glm::vec3& LightCaster::getColor() const
		{
			return m_Color;
		}

		float LightCaster::getIntensity() const
		{
			return m_Intensity;
		}

		LightCaster::~LightCaster()
		{
		}
	}
}
