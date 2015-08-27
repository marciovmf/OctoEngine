#include "texture.h"
#include <SOIL.h>

namespace octo {
	namespace graphics {

		Texture::Texture(const char* name, unsigned char* data, int width, int height) 
			:Resource(name), m_Data(data), m_Width(width), m_Height(height)
		{
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		Texture::~Texture()
		{
			SOIL_free_image_data(m_Data);
		}

	}
}