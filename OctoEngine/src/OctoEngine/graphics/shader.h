#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../resources/resource.h"
#include <map>

namespace octo
{
	namespace graphics
	{
		// Controls which sides of polygons should be culled (not drawn)
		enum CULL
		{
			BACK,
			FRONT,
			OFF
		};

		// Controls how should depth testing be performed (if enabled).
		// Default is LEqual(draw objects in from or at the distance as existing objects; hide objects behind them).
		enum ZTEST
		{
			NEVER = GL_NEVER,
			LESS = GL_LESS,
			EQUAL = GL_EQUAL,
			LEQUAL = GL_LEQUAL,
			GREATER = GL_GREATER,
			NOTEQUAL = GL_NOTEQUAL,
			GEQUAL = GL_GEQUAL,
			ALWAYS = GL_ALWAYS
		};

		class Shader : public octo::resources::Resource
		{
		private:
			Shader(const char* reosourceId, const char* vertexShaderFile, const char* fragmentShaderFile);
		public:
			~Shader() override;
			void bind() const;
			void unbind() const;
			GLuint getUniformLocation(const GLchar* uniform);
			GLuint getAttributeLocation(const GLchar* attribute);


			void setUniform(const GLchar* uniform, GLint value);
			void setUniform(const GLchar* uniform, glm::vec2 value);
			void setUniform(const GLchar* uniform, glm::vec3 value);
			void setUniform(const GLchar* uniform, glm::vec4 value);
			void setUniform(const GLchar* uniform, GLfloat value);
			void setUniform(const GLchar* uniform, GLuint value);
			void setUniform(const GLchar* uniform, glm::mat4 value);
			bool ZWrite() const;
			void ZWrite(bool b);
			ZTEST ZTest() const;
			void ZTest(ZTEST test);
			CULL Cull() const;
			void Cull(CULL mode);

			static octo::resources::Resource* load(const char* resourceName);

		private:
			GLuint m_VertexShader;
			GLuint m_FragmentShader;
			GLuint m_ShaderProgram;
			std::map<const GLchar*, GLuint> m_CachedLocations;

			Shader& operator=(Shader& other) = delete;

			bool m_ZWrite;
			ZTEST m_ZTest;
			CULL m_Cull;

			static bool s_ZWrite;
			static ZTEST s_ZTest;
			static CULL s_Cull;
		};
	}
}
