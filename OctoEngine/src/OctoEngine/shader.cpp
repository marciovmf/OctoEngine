#include "shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

namespace octo {
	namespace graphics {

		std::unique_ptr<std::string> LoadShaderSource(const char* fileName);
		GLint CheckShaderCompilation(GLuint shader);
		GLint CheckProgramLink(GLuint program);

		Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
		{
			const char* EMPTY_SHADER_SOURCE = "";

			// Set up the Vertex Shader
			std::unique_ptr<std::string> pShaderSource = LoadShaderSource(vertexShaderFile);
			char* shaderSource = ((pShaderSource) ? (char*)(*pShaderSource).c_str() : (char*)(EMPTY_SHADER_SOURCE));
			m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(m_VertexShader, 1, &shaderSource, NULL);
			glCompileShader(m_VertexShader);
			CheckShaderCompilation(m_VertexShader);

			// Set up the Fragment Shader
			pShaderSource = LoadShaderSource(fragmentShaderFile);
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

		void Shader::Bind() const
		{
			glUseProgram(m_ShaderProgram);
		}

		void Shader::Unbind() const
		{
			glUseProgram(0);
		}


		GLuint Shader::GetUniformLocation(const GLchar* uniform) const
		{
			return glGetUniformLocation(m_ShaderProgram, uniform);
		}

		GLuint Shader::GetAttributeLocation(const GLchar* attribute) const
		{
			return glGetAttribLocation(m_ShaderProgram, attribute);
		}

		void Shader::SetUniform(const GLchar* uniform, glm::vec2 value) const
		{
			glUniform2f(GetUniformLocation(uniform), value.x, value.y);
		}

		void Shader::SetUniform(const GLchar* uniform, glm::vec3 value) const
		{
			glUniform3f(GetUniformLocation(uniform), value.x, value.y, value.z);
		}

		void Shader::SetUniform(const GLchar* uniform, glm::vec4 value) const
		{
			glUniform4f(GetUniformLocation(uniform), value.x, value.y, value.z, value.w);
		}

		void Shader::SetUniform(const GLchar* uniform, GLfloat value) const
		{
			glUniform1f(GetUniformLocation(uniform), value);
		}

		void Shader::SetUniform(const GLchar* uniform, GLuint value) const
		{
			glUniform1i(GetUniformLocation(uniform), value);
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