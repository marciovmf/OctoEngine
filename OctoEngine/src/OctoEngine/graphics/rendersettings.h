#pragma once
//#include <glm/detail/type_vec3.hpp>
#include <glm/glm.hpp>


namespace octo
{
	namespace graphics
	{
		// Stores global settings that affects rendering systemwide
		struct RenderSettings
		{
		public:
			static glm::vec3 AmbientLightColor;
			// FOG settings goes here
		};
	}
}
