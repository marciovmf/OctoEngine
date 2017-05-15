#pragma once

#include <vector>
#include <GL/glew.h>
#include "vertex.h"


#define MAX_DIFFUSE_TEXTURES 3

namespace octo
{
	namespace graphics
	{
		class Mesh
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			//GLuint m_IBO;

			const std::vector<Vertex>& m_Vertices;

			//const std::vector<GLuint>& m_Indices;
			enum
			{
				RENDERER_VERTEX_INDEX = 0,
				RENDERER_NORMAL_INDEX,
				RENDERER_TEXCOORD_INDEX,
			};

		private:
			Mesh(Mesh& other) = delete;

		public:
			Mesh(const std::vector<Vertex>& vertices/*, const std::vector<GLuint>& indices*/);
			~Mesh();
			void Render() const;

			inline const std::vector<Vertex>& getVertices() const
			{
				return m_Vertices;
			}

			//inline const std::vector<GLuint>& getIndices() const { return m_Indices; }
		};
	}
}
