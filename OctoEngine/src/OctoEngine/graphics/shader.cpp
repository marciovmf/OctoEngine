#include "shader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <tinyxml2.h>
#include <algorithm>

namespace octo
{
	namespace graphics
	{
		//		std::unique_ptr<std::string> LoadShaderSource(const char* fileName);
		GLint checkShaderCompilation(GLuint shader);
		GLint checkProgramLink(GLuint program);

		// Default states
		bool Shader::s_ZWrite = true;
		ZTEST Shader::s_ZTest = ZTEST::LESS;
		CULL Shader::s_Cull = CULL::OFF;

		Shader::Shader(const char* reosourceId, const char* vertexShader, const char* fragmentShader) :
			octo::resources::Resource(reosourceId)
		{
			
			m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(m_VertexShader, 1, &vertexShader, NULL);
			glCompileShader(m_VertexShader);
			checkShaderCompilation(m_VertexShader);

			m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(m_FragmentShader, 1, &fragmentShader, NULL);
			glCompileShader(m_FragmentShader);
			checkShaderCompilation(m_FragmentShader);

			// Shader Program
			m_ShaderProgram = glCreateProgram();
			glAttachShader(m_ShaderProgram, m_VertexShader);
			glDeleteShader(m_VertexShader);
			glAttachShader(m_ShaderProgram, m_FragmentShader);
			glDeleteShader(m_FragmentShader);

			glLinkProgram(m_ShaderProgram);
			checkProgramLink(m_ShaderProgram);
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
					glDisable(GL_CULL_FACE);

				// Set face culling mode
				glCullFace(((m_Cull == CULL::BACK) ? GL_BACK : GL_FRONT));

				// cache the current mode
				s_Cull = m_Cull;
			}

			// Enable/disable Z-Writing
			/*if (m_ZWrite != s_ZWrite)
			{
				glDepthMask((GLboolean)m_ZWrite);
				s_ZWrite = m_ZWrite;
			}*/

			// Set Depth function (only if zwrite is enabled)
			//if (m_ZTest != s_ZTest /* && m_ZWrite*/)
			//{
			//	glDepthFunc((GLenum)m_ZTest);
			//	s_ZTest = m_ZTest;
			//}

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
			/*else
			{
				std::cout << glGetError() <<  ":ERROR: Could not find location for uniform '" << uniform << "'" << std::endl;
			}*/

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
			std::unique_ptr<std::string> result(nullptr);

			try
			{
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

		GLint checkShaderCompilation(GLuint shader)
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

		GLint checkProgramLink(GLuint program)
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

		octo::resources::Resource* Shader::load(const char* resourceName)
		{
			tinyxml2::XMLDocument xmlDoc;
			tinyxml2::XMLError error = xmlDoc.LoadFile(resourceName);

			if (error != tinyxml2::XMLError::XML_SUCCESS)
			{
				// TODO: Log that could not load the asset
				return nullptr;
			}

			std::hash<std::string> strHash;

			tinyxml2::XMLElement* ShaderElement = xmlDoc.FirstChildElement("SHADER");
			if (ShaderElement == nullptr)
				return false;

			tinyxml2::XMLElement* vertexElement = ShaderElement->FirstChildElement("VERTEX");
			tinyxml2::XMLElement* fragmentElement = ShaderElement->FirstChildElement("FRAGMENT");
			//tinyxml2::XMLElement *GeometryElement = ShaderElement->FirstChildElement("GEOMETRY");
			tinyxml2::XMLElement* capabilityCull = ShaderElement->FirstChildElement("CULL");
			tinyxml2::XMLElement* capabilityZWrite = ShaderElement->FirstChildElement("ZWRITE");
			tinyxml2::XMLElement* capabilityZTest = ShaderElement->FirstChildElement("ZTEST");

			// create a Shader object
			octo::graphics::Shader* shader = new octo::graphics::Shader(
				resourceName, 
				vertexElement->GetText(), 
				fragmentElement->GetText());

			
			// Parse CULL option
			if (capabilityCull != nullptr)
			{
				std::string s = capabilityCull->GetText();
				std::transform(s.begin(), s.end(), s.begin(), tolower);
				const size_t keyHash = std::hash<std::string>()(s);

				if (keyHash == strHash("back"))
					shader->Cull(octo::graphics::CULL::BACK);
				else if (keyHash == strHash("front"))
					shader->Cull(octo::graphics::CULL::FRONT);
				else if (keyHash == strHash("off"))
					shader->Cull(octo::graphics::CULL::OFF);
				else
				{
					std::cout << "ERROR: Invalid value for CULL option." << std::endl;
					shader->Cull(octo::graphics::CULL::BACK);
				}
			}

			// Parse ZWRITE options
			if (capabilityZWrite != nullptr)
			{
				std::string s = capabilityZWrite->GetText();
				std::transform(s.begin(), s.end(), s.begin(), tolower);
				const size_t keyHash = std::hash<std::string>()(s);

				if (keyHash == strHash("off"))
					shader->ZWrite(false);
				else if (keyHash == strHash("on") || keyHash == strHash("enabled"))
					shader->ZWrite(true);
				else
				{
					std::cout << "ERROR: Invalid value for ZWRITE option." << std::endl;
					shader->Cull(octo::graphics::CULL::BACK);
				}
			}

			// Parse ZTEST options only if ZWRITE is enabled
			if (capabilityZTest != nullptr && shader->ZWrite())
			{
				std::string s = capabilityZTest->GetText();
				std::transform(s.begin(), s.end(), s.begin(), tolower);
				const size_t keyHash = std::hash<std::string>()(s);

				if (keyHash == strHash("never"))
				{
					shader->ZTest(ZTEST::NEVER);
				}
				else if (keyHash == strHash("less")) 
				{
					shader->ZTest(ZTEST::LESS);
				}
				else if (keyHash == strHash("greater"))
				{
					shader->ZTest(ZTEST::GREATER);
				}
				else if (keyHash == strHash("equal"))
				{
					shader->ZTest(ZTEST::EQUAL);
				}
				else if (keyHash == strHash("always"))
				{
					shader->ZTest(ZTEST::ALWAYS);
				}
				else if (keyHash == strHash("lequal"))
				{
					shader->ZTest(ZTEST::LEQUAL);
				}
				else if (keyHash == strHash("gequal"))
				{
					shader->ZTest(ZTEST::GEQUAL);
				}
				else if (keyHash == strHash("notequal"))
				{
					shader->ZTest(ZTEST::NOTEQUAL);
				}
				else
				{
					std::cout << "ERROR: Invalid value for ZTEST option." << std::endl;
					shader->Cull(octo::graphics::CULL::BACK);
				}
			}

			if (vertexElement == nullptr || fragmentElement == nullptr)
				return nullptr;

			return shader;
		}
	}
}
