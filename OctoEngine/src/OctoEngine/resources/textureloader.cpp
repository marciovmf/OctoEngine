#include "textureloader.h"
#include "texture.h"
#include <SOIL.h>

namespace octo {
	namespace resources {

		TextureLoader::TextureLoader()
		{
			// Make sure the Resource Manager is initialized and assign this isntance as the loader for TEXTUREs
			/*ResourceManager::Initialize();
			ResourceManager::getInstance().registerLoader<Texture>(this);*/
		}

		TextureLoader::~TextureLoader()
		{
		}

		
		Resource* TextureLoader::loadResource(const char* resourceName) 
		{
			int w =0, h =0;
			unsigned char* data = SOIL_load_image(resourceName, &w, &h, 0, SOIL_LOAD_RGBA);
			return new Texture(resourceName, data, w, h);

		}

		//void TextureLoader::unloadResource(std::shared_ptr<Texture> resourcePtr)
		//{
		//	////SOIL_free_image_data(static_cast<std::shared_ptr<Texture>>(resourcePtr.get())->getData());
		//	//SOIL_free_image_data(resourcePtr.get())->getData());
		//	//
		//	//resourcePtr.reset();		
		//}

	}
}