#pragma once
#include "../resources/resource.h"
#include <GL/glew.h>

namespace octo {
	namespace graphics {

		struct CubeMapData
		{
			GLsizei width;
			GLsizei height;
			const unsigned char* front;
			const unsigned char* back;
			const unsigned char* left;
			const unsigned char* right;
			const unsigned char* up;
			const unsigned char* down;

			CubeMapData();
			~CubeMapData();
		};

		class CubeMap  : public octo::resources::Resource
		{
		private:
			const CubeMapData* m_CubeMapData;
			GLuint m_CubeMapId;
		public:
			CubeMap(const char* reosourceId, const CubeMapData* cubeMapData);
			~CubeMap();

			inline const CubeMapData& getCubeMapData() const { return *m_CubeMapData;  };

			inline void bind() const
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapId);
			};

			inline void unbind() const
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			};

			static octo::resources::Resource* load(const char* resourceName);
		};

	}
}

