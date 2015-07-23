#pragma once

#include <vector>
#include <GL\glew.h>
#include "buffer.h"

namespace octo {
	namespace graphics {

		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();
			void addBuffer(Buffer* buffer, GLuint attributeLocation);
			void bind() const;
			void unbind() const;

		private:
			VertexArray(VertexArray& other){}
			VertexArray& operator=(VertexArray& other){}
		};

	}
}

