#include "shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include "../core/utils.h"
#include <glm/gtc/type_ptr.hpp>
#include "../core/exception/exception.h"

namespace octo {
	namespace graphics {


		//		std::unique_ptr<std::string> LoadShaderSource(const char* fileName);
		GLint CheckShaderCompilation(GLuint shader);
		GLint CheckProgramLink(GLuint program);

		// Default states
		bool Shader::s_ZWrite = true;
		ZTEST Shader::s_ZTest = ZTEST::LESS;
		CULL Shader::s_Cull = CULL::OFF;


		Shader::Shader(const char* reosourceId, const char* vertexShaderFile, const char* fragmentShaderFile) :
			octo::resources::Resource(reosourceId)
		{
			const char* EMPTY_SHADER_SOURCE = "";

			// Set up the Vertex Shader
			std::unique_ptr<std::string> pShaderSource = octo::LoadFile(vertexShaderFile);
			char* shaderSource = ((pShaderSource) ? (char*)(*pShaderSource).c_str() : (char*)(EMPTY_SHADER_SOURCE));
			m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(m_VertexShader, 1, &shaderSource, NULL);
			glCompileShader(m_VertexShader);
			CheckShaderCompilation(m_VertexShader);

			// Set up the Fragment Shader
			pShaderSource = octo::LoadFile(fragmentShaderFile);
			shaderSource = ((pShaderSource) ? (char*)(*pShaderSource).c_str() : (char*)EMPTY_SHADER_SOURCE);
			m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(m_FragmentShader, 1, &shaderSource, NULL);
			glCompileShader(m_FragmentShader);
			CheckShaderCompilation(m_FragmentShader);

			// Shader Program
			m_ShaderProgram = glCreateProgram();
			glAttachShader(m_ShaderProgram, m_VertexShader);
			glDeleteShader(m_VertexShader);
			glAttachShader(m_ShaderProgram, m_FragmentShader);
			glDeleteShader(m_FragmentShader);

			glLinkProgram(m_ShaderProgram);
			CheckProgramLink(m_ShaderProgram);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderProgram);
		}

		void Shader::bind() const
		{
			// Set FACE CULLING
			if (m_Cull != s_Cull)
			{
				// Enable/Disable face culling
				if (m_Cull != CULL::OFF)
					glEnable(GL_CULL_FACE);
				else
					glEnable(GL_CULL_FACE);

				// Set face culling mode
				glCullFace( ((m_Cull == CULL::BACK) ? GL_BACK : GL_FRONT ) );

				// cache the current mode
				s_Cull = m_Cull;
			}

			// Enable/disable Z-Writing
			if (m_ZWrite != s_ZWrite)
			{
				glDepthMask(m_ZWrite);
				s_ZWrite = m_ZWrite;
			}

			// Set Depth function
			if ( m_ZTest != s_ZTest)
			{
				glDepthFunc((GLenum)m_ZTest);
				s_ZTest = m_ZTest;
			}

			// Depth testing
			glUseProgram(m_ShaderProgram);
		}

		void Shader::unbind() const
		{
			glUseProgram(0);
		}

		GLuint Shader::getUniformLocation(const GLchar* uniform)
		{
			if (m_CachedLocations.find(uniform) != m_CachedLocations.end())
				return m_CachedLocations[uniform];

			GLint location = glGetUniformLocation(m_ShaderProgram, uniform);
			if (location > -1)
				m_CachedLocations[uniform] = location;

			return location;
		}

		GLuint Shader::getAttributeLocation(const GLchar* attribute)
		{
			if (m_CachedLocations.find(attribute) != m_CachedLocations.end())
				return m_CachedLocations[attribute];

			GLint location = glGetAttribLocation(m_ShaderProgram, attribute);
			if (location > -1)
				m_CachedLocations[attribute] = location;

			return location;
		}

		void Shader::setUniform(const GLchar* uniform, GLint value)
		{
			glUniform1i(getUniformLocation(uniform), value);
		}

		void Shader::setUniform(const GLchar* uniform, glm::vec2 value)
		{
			glUniform2f(getUniformLocation(uniform), value.x, value.y);
		}

		void Shader::setUniform(const GLchar* uniform, glm::vec3 value)
		{
			glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
		}

		void Shader::setUniform(const GLchar* uniform, glm::vec4 value)
		{
			glUniform4f(getUniformLocation(uniform), value.x, value.y, value.z, value.w);
		}

		void Shader::setUniform(const GLchar* uniform, GLfloat value)
		{
			glUniform1f(getUniformLocation(uniform), value);
		}

		void Shader::setUniform(const GLchar* uniform, GLuint value)
		{
			glUniform1i(getUniformLocation(uniform), value);
		}

		bool Shader::ZWrite() const
		{
			return m_ZWrite;
		}

		void Shader::ZWrite(bool b)
		{
			m_ZWrite = b;
		}

		ZTEST Shader::ZTest() const
		{
			return m_ZTest;
		}

		CULL Shader::Cull() const
		{
			return m_Cull;
		}

		void Shader::Cull(CULL mode)
		{
			m_Cull = mode;
		}

		void Shader::ZTest(ZTEST test)
		{
			m_ZTest = test;
		}

		void Shader::setUniform(const GLchar* uniform, glm::mat4 value)
		{
			glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(value));
		}

		std::unique_ptr<std::string> LoadShaderSource(const char* fileName)
		{
			std::unique_ptr <std::string> result(nullptr);

			try {
				std::ifstream file;
				file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				file.open(fileName);
				std::stringstream source;

				source << file.rdbuf();
				file.close();
				result = std::make_unique<std::string>(source.str());
			}
			catch (std::exception e)
			{
				std::cerr << "[ERROR]:" << fileName << e.what() << std::endl;
			}
			return result;
		}

		GLint CheckShaderCompilation(GLuint shader)
		{
			GLint success = 0;
			GLchar infoLog[512];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
				std::cerr << "ERROR: SHADER COMPILATION FAILED:" << infoLog << std::endl;
			}

			return success;
		}

		GLint CheckProgramLink(GLuint program)
		{
			GLint success = 0;
			GLchar infoLog[512];

			glGetProgramiv(program, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
				std::cerr << "ERROR: PROGRAM LINKING FAILED:" << infoLog << std::endl;
			}

			return success;
		}

	}
}