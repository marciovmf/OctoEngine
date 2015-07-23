#pragma once
#include "resource.h"
#include <SOIL.h>

namespace octo {
	namespace resources {

		class Texture : public Resource
		{
		private:
			int m_Width;
			int m_Height;
			unsigned char* m_Data;
			static short int m_TypeID;
		public:
			Texture(const char* name, unsigned char* data, int width, int height);
			~Texture();
			inline int getWidth() const { return m_Width;}
			inline int getHeight() const { return m_Height;}
			inline unsigned char* const getData() const { return m_Data; }
		};

	}
}
