#pragma once
#include <GL/glew.h>

namespace octo {
	namespace graphics {

		/// <summary>
		//A buffer for storing vertex data for OpenGL rendering;
		//The data can be anything, such as color, UV coords etc.
		/// </summary>
		class Buffer
		{

		public:
			enum BufferType {
				VERTEX_DATA = GL_ARRAY_BUFFER,				// This buffer is a VERTEX data buffer
				INDEX_DATA = GL_ELEMENT_ARRAY_BUFFER			// this buffer is an INDEX data buffer
			};

		private:
			GLuint m_BufferId;
			GLuint m_ComponentCount;
			BufferType m_BufferType;
			GLenum m_ElementDataType;
			GLsizei m_ElementCount;
			
		public:

			explicit Buffer(GLint* data, GLsizei elementCount, const GLuint componentCount, BufferType type = BufferType::VERTEX_DATA);
			explicit Buffer(GLuint* data, GLsizei elementCount, const GLuint componentCount, BufferType type = BufferType::VERTEX_DATA);
			explicit Buffer(GLfloat* data, GLsizei elementCount, const GLuint componentCount, BufferType type = BufferType::VERTEX_DATA);
			explicit Buffer(GLushort* data, GLsizei elementCount, const GLuint componentCount, BufferType type = BufferType::VERTEX_DATA);

			~Buffer();
			void bind() const;
			void unbind() const;
			inline GLuint getComponentCount() const { return m_ComponentCount; } 
			inline GLenum getBufferElementType() const { return m_ElementDataType; } 
			inline GLsizei getCount() const { return m_ElementCount; }
		private:
			Buffer(Buffer& other){};
			Buffer& operator=(Buffer& other){};
			int sizeofElementDataType() const;
			void Buffer::init(GLvoid* data, GLsizei elementCount);
		};

	}
}