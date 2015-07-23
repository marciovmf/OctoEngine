#include "vertexarray.h"

namespace octo {
	namespace graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID);

		}


		VertexArray::~VertexArray()
		{
			for (unsigned int i = 0; i < m_Buffers.size(); i++)
			{
				delete m_Buffers[i];
			}

			//TODO: check if deleting this causes any performance hit
			//glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_ArrayID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArray::addBuffer(Buffer* buffer, GLuint attributeLocation)
		{
			bind();
			buffer->bind();
				glEnableVertexAttribArray(attributeLocation);
				glVertexAttribPointer(attributeLocation,
					buffer->getComponentCount(),
					buffer->getBufferElementType(),
					GL_FALSE,
					0,
					(const void*)0);
			buffer->unbind();
			unbind();

			m_Buffers.push_back(buffer);
		}

	}
}