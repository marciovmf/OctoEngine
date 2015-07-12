#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

namespace octo {
	namespace graphics {

		class Shader
		{
		public:
			Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
			virtual ~Shader();
			void Bind() const;
			void Unbind() const;
			GLuint GetUniformLocation(const GLchar* uniform) const;
			GLuint GetAttributeLocation(const GLchar* attribute) const;

			void SetUniform(const GLchar* uniform, glm::vec2 value) const;
			void SetUniform(const GLchar* uniform, glm::vec3 value) const;
			void SetUniform(const GLchar* uniform, glm::vec4 value) const;
			void SetUniform(const GLchar* uniform, GLfloat value) const;
			void SetUniform(const GLchar* uniform, GLuint value) const;

		private:
			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_ShaderProgram;
			Shader& operator=(Shader& other){}

		};

	}
}
