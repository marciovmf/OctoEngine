#pragma once
#include "../components/component.h"
#include "../../graphics/AmbientLight.h"

namespace octo
{
	namespace core
	{
		class IRenderer :
			public octo::core::Component
		{
		private:
			//octo::graphics::AmbientLight m_AmbientLight;

		public:
			IRenderer();
			virtual ~IRenderer();

			//void setAmbientLight(const octo::graphics::AmbientLight& ambientLight);
			//const graphics::AmbientLight& getAmbientLight() const;
		};
	}
}
