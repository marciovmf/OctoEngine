#pragma once
#include <memory>
#include "resourceloader.h"
#include "texture.h"

namespace octo {
	namespace resources {

		class Resource;

		typedef std::shared_ptr < Texture > TextureResource;

		class TextureLoader : public ResourceLoader
		{
		public:
			TextureLoader();
			~TextureLoader();
			
			Resource* loadResource(const char* resourceName) override;

			//template <typename T>	void unloadResource(std::shared_ptr<T> resourcePtr) override;
		};
	}
}

