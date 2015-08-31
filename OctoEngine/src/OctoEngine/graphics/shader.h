#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../resources/resource.h"
#include <map>

namespace octo {
	namespace graphics {

		class Shader : public octo::resources::Resource
		{
		public:
			Shader(const char* reosourceId, const char* vertexShaderFile, const char* fragmentShaderFile);
			~Shader() override;
			void bind() const;
			void unbind() const;
			GLuint getUniformLocation(const GLchar* uniform) ;
			GLuint getAttributeLocation(const GLchar* attribute);
			

			void setUniform(const GLchar* uniform, GLint value) ;
			void setUniform(const GLchar* uniform, glm::vec2 value) ;
			void setUniform(const GLchar* uniform, glm::vec3 value) ;
			void setUniform(const GLchar* uniform, glm::vec4 value) ;
			void setUniform(const GLchar* uniform, GLfloat value) ;
			void setUniform(const GLchar* uniform, GLuint value) ;
			void setUniform(const GLchar* uniform, glm::mat4 value) ;

		private:
			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_ShaderProgram;
			std::map<const GLchar*, GLuint> m_CachedLocations;
			Shader& operator=(Shader& other){}

		};

	}
}
