#include "Buffer.h"
#include <cassert>
#include <type_traits>

namespace octo {
	namespace graphics {


		Buffer::Buffer(GLint* data, GLsizei elementCount, const GLuint componentCount, BufferType type)
			: m_ElementCount(elementCount), m_ComponentCount(componentCount), m_BufferType(type), m_ElementDataType(GL_INT)
		{
			init(data, elementCount);
		}

		Buffer::Buffer(GLuint* data, GLsizei elementCount, const GLuint componentCount, BufferType type)
			: m_ElementCount(elementCount), m_ComponentCount(componentCount), m_BufferType(type), m_ElementDataType(GL_UNSIGNED_INT)
		{
			init(data, elementCount);
		}

		Buffer::Buffer(GLfloat* data, GLsizei elementCount, const GLuint componentCount, BufferType type)
			: m_ElementCount(elementCount), m_ComponentCount(componentCount), m_BufferType(type), m_ElementDataType(GL_FLOAT)
		{
			init(data, elementCount);
		}

		Buffer::Buffer(GLushort* data, GLsizei elementCount, const GLuint componentCount, BufferType type)
			: m_ElementCount(elementCount), m_ComponentCount(componentCount), m_BufferType(type), m_ElementDataType(GL_UNSIGNED_SHORT)
		{
			init(data, elementCount);
		}

		void Buffer::init(GLvoid* data, GLsizei elementCount)
		{
			//OpenGL requires component count to be between 1 and 4
			assert(m_ComponentCount > 0 && m_ComponentCount < 4);

			glGenBuffers(1, &m_BufferId);
			glBindBuffer(m_BufferType, m_BufferId);
			glBufferData(m_BufferType,							// Just an array of data
				elementCount * sizeofElementDataType(),			// number of "objects" in this buffer
				data,											// pointer to the actual data
				GL_STATIC_DRAW);								// this data is static and will not be modified
			glBindBuffer(m_BufferType, 0);
		}

		int Buffer::sizeofElementDataType() const
		{
			if (m_ElementDataType == GL_INT)
				return sizeof(GLint);

			if (m_ElementDataType == GL_UNSIGNED_INT)
				return sizeof(GLuint);

			if (m_ElementDataType == GL_UNSIGNED_BYTE)
				return sizeof(GLubyte);

			// default
			return sizeof(GLfloat);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_BufferId);
		}


		void Buffer::bind() const
		{
			glBindBuffer(m_BufferType, m_BufferId);
		}


		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}



	}
}