#include "material.h"
#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
namespace octo
{
	namespace graphics
	{
		Material::Material(const char* resourceName, std::shared_ptr<Shader> shaderResourcePtr)
			: Resource(resourceName), m_Shader(shaderResourcePtr)
		{	}

		Material::Material(const char* resourceName)
			: Resource(resourceName)
		{	}

		void Material::setShader(std::shared_ptr<Shader> shader)
		{
			m_Shader = shader;
		}

		void Material::addFloat(std::string name, float value)
		{
			m_FloatValues[name] = value;
		}

		void Material::addInt(std::string name, int value)
		{
			m_IntValues[name] = value;
		}

		void Material::addVec4(std::string name, glm::vec4 value)
		{
			m_Vec4Values[name] = value;
		}

		void Material::addVec3(std::string name, glm::vec3 value)
		{
			m_Vec3Values[name] = value;
		}

		void Material::addVec2(std::string name, glm::vec2 value)
		{
			m_Vec2Values[name] = value;
		}

		void Material::addTexture(std::string name, std::shared_ptr<Texture> textureResource)
		{
			m_Textures[name] = textureResource;
		}

		std::shared_ptr<Shader> Material::getShader()
		{
			return m_Shader;
		}

		float Material::getFloat(const char* name)
		{
			auto it = m_FloatValues.find(name);
			return ((it == m_FloatValues.end()) ? 0.0f : it->second);
		}

		int Material::getInt(const char* name)
		{
			auto it = m_IntValues.find(name);
			return ((it == m_IntValues.end()) ? 0 : it->second);
		}

		glm::vec4 Material::getVec4(const char* name)
		{
			auto it = m_Vec4Values.find(name);
			return ((it == m_Vec4Values.end()) ? glm::vec4(0,0,0,0) : it->second);
		}

		glm::vec3 Material::getVec3(const char* name)
		{
			auto it = m_Vec3Values.find(name);
			return ((it == m_Vec3Values.end()) ? glm::vec3(0, 0, 0) : it->second);
		}

		glm::vec2 Material::getVec2(const char* name)
		{
			auto it = m_Vec2Values.find(name);
			return ((it == m_Vec2Values.end()) ? glm::vec2(0, 0) : it->second);
		}

		void Material::bind()
		{			
			// Enable texture units
			GLint textureUnit = 0;
			for (auto texture : m_Textures)
			{
				glActiveTexture(GL_TEXTURE0 + textureUnit);
				texture.second->bind();
				textureUnit++;
				m_Shader->setUniform( texture.first.c_str() ,textureUnit);
			}
			
			// bind to the shader
			m_Shader->bind();

			// Set the defined uniforms
			for (std::pair<std::string, float> uniform : m_FloatValues)
			{
				this->m_Shader->setUniform(uniform.first.c_str(), uniform.second);
			}

			for (std::pair<std::string, int> uniform : m_IntValues)
			{
				this->m_Shader->setUniform(uniform.first.c_str(), uniform.second);
			}

			for (std::pair<std::string, glm::vec3> uniform : m_Vec3Values)
			{
				this->m_Shader->setUniform(uniform.first.c_str(), uniform.second);
			}

			for (std::pair<std::string, glm::vec2> uniform : m_Vec2Values)
			{
				this->m_Shader->setUniform(uniform.first.c_str(), uniform.second);
			}

			for (std::pair<std::string, glm::vec4> uniform : m_Vec4Values)
			{
				this->m_Shader->setUniform(uniform.first.c_str(), uniform.second);
			}
		}


		void Material::unbind()
		{
			m_Shader->unbind();
		}

		std::shared_ptr<graphics::Texture> Material::getTexture(const char* name)
		{
			auto it = m_Textures.find(name);
			return ((it == m_Textures.end()) ? nullptr : it->second);
		}

		Material::~Material()
		{
		}

	}
}