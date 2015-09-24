#pragma once

#include "lightcaster.h"

namespace octo {
	namespace core {

		class DirectionalLight : public octo::core::LightCaster
		{
		public:
			DirectionalLight();
			~DirectionalLight();
		};
	}
}

