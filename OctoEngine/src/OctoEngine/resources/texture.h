#pragma once
#include "resource.h"
#include <SOIL.h>
#include <GL/glew.h>
#include <memory>

namespace octo {
	namespace resources {

		class Texture : public Resource
		{
		private:
			int m_Width;
			int m_Height;
			unsigned char* m_Data;
			static short int m_TypeID;
			GLuint m_TextureID;
		public:
			Texture(const char* name, unsigned char* data, int width, int height);
			~Texture();
			inline int getWidth() const { return m_Width;}
			inline int getHeight() const { return m_Height;}
			inline unsigned char* const getData() const { return m_Data; }
			inline GLuint getTextureID() const { return m_TextureID;  }
			inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_TextureID); };
			inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };
		};
		
		typedef std::shared_ptr<Texture> TextureResource;
	}
}
