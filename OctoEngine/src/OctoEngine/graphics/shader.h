#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../resources/resource.h"

namespace octo {
	namespace graphics {

		class Shader : public octo::resources::Resource
		{
		public:
			Shader(const char* reosourceId, const char* vertexShaderFile, const char* fragmentShaderFile);
			~Shader() override;
			void bind() const;
			void unbind() const;
			GLuint getUniformLocation(const GLchar* uniform) const;
			GLuint getAttributeLocation(const GLchar* attribute) const;

			void setUniform(const GLchar* uniform, GLint value) const;
			void setUniform(const GLchar* uniform, glm::vec2 value) const;
			void setUniform(const GLchar* uniform, glm::vec3 value) const;
			void setUniform(const GLchar* uniform, glm::vec4 value) const;
			void setUniform(const GLchar* uniform, GLfloat value) const;
			void setUniform(const GLchar* uniform, GLuint value) const;
			void setUniform(const GLchar* uniform, glm::mat4 value) const;

		private:
			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_ShaderProgram;
			Shader& operator=(Shader& other){}

		};

	}
}
