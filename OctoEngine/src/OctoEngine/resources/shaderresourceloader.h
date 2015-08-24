#pragma once
#include "resourceloader.h"
#include "resource.h"

namespace octo
{
	namespace resources
	{
		class ShaderResourceLoader : public ResourceLoader
		{
		public:

			ShaderResourceLoader();
			~ShaderResourceLoader() override;
			octo::resources::Resource* loadResource(const char* resourceName) override;
		};


	}
}
