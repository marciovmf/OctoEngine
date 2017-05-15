#pragma once
#include <glm/detail/type_vec3.hpp>

namespace octo
{
	namespace graphics
	{
		struct AmbientLight
		{
			AmbientLight();
			AmbientLight(float r, float g, float b, float intensity);
			glm::vec3 color;
			float intensity;
		};

		inline AmbientLight::AmbientLight():color(1, 1, 1),intensity(0.2f)
		{
		}

		inline AmbientLight::AmbientLight(float r, float g, float b, float intensity):color(r, g, b), intensity(intensity)
		{
		}
	}
}
