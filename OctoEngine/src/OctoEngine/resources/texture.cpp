#include "texture.h"
#include <SOIL.h>


namespace octo {
	namespace resources {

		Texture::Texture(const char* name, unsigned char* data, int width, int height) 
			:Resource(name), m_Data(data), m_Width(width), m_Height(height)
		{
		}


		Texture::~Texture()
		{
			SOIL_free_image_data(m_Data);
		}

	}
}