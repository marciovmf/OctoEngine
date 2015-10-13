#include "material.h"
#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include "tinyxml2.h"
#include <algorithm>
#include <sstream>
#include "cubemap.h"
#include "../resources/resourcemanager.h"

namespace octo
{
	namespace graphics
	{
		Material::Material(const char* resourceName, std::shared_ptr<Shader> shaderResourcePtr)
			: Resource(resourceName), m_Shader(shaderResourcePtr)
		{
		}

		Material::Material(const char* resourceName)
			: Resource(resourceName)
		{
		}

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

		void Material::addCubeMap(std::string name, std::shared_ptr<CubeMap> cubeMapResource)
		{
			m_CubeMaps[name] = cubeMapResource;
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
			return ((it == m_Vec4Values.end()) ? glm::vec4(0, 0, 0, 0) : it->second);
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
				glActiveTexture(GL_TEXTURE0 + textureUnit );
				texture.second->bind();
				textureUnit++;
				m_Shader->setUniform(texture.first.c_str(), textureUnit);
			}
			
			// Enable texture units for cubemaps
			for (auto cubemap : m_CubeMaps)
			{
				glActiveTexture(GL_TEXTURE0 + textureUnit);
				cubemap.second->bind();
				textureUnit++;
				m_Shader->setUniform(cubemap.first.c_str(), textureUnit);
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

		std::shared_ptr<graphics::CubeMap>  Material::getCubeMap(const char* name)
		{
			auto it = m_CubeMaps.find(name);
			return ((it == m_CubeMaps.end()) ? nullptr : it->second);
		}

		Material::~Material()
		{
		}

		octo::resources::Resource* Material::load(const char* resourceName)
		{
			tinyxml2::XMLDocument xmlDoc;
			//std::cout << "Loading material '" << resourceName << "'" << std::endl;

			tinyxml2::XMLError error = xmlDoc.LoadFile(resourceName);

			if (error != tinyxml2::XMLError::XML_SUCCESS)
			{
				// TODO: Log that could not load the asset
				std::cout << "ERROR: Error loading xml file:" << error << std::endl;
				return nullptr;
			}

			tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("material");

			// Precalculate hash values for faster name comparing
			std::hash<std::string> strHash;
			size_t VECTOR4_HASH = strHash("vec4");
			size_t VECTOR3_HASH = strHash("vec3");
			size_t VECTOR2_HASH = strHash("vec2");
			size_t FLOAT_HASH = strHash("float");
			size_t INT_HASH = strHash("int");
			size_t SHADER_HASH = strHash("shader");
			size_t TEXTURE_HASH = strHash("texture");
			size_t CUBEMAP_HASH = strHash("cubemap");

			short int shaderCount = 0;

			// Pointers for image data
			unsigned char* dataFront = nullptr;
			unsigned char* dataBack = nullptr;
			unsigned char* dataLeft = nullptr;
			unsigned char* dataRight = nullptr;
			unsigned char* dataUp = nullptr;
			unsigned char* dataDown = nullptr;

			// Creates an empty material instance
			graphics::Material* ptrMaterial = new graphics::Material(resourceName);

			for (tinyxml2::XMLElement* child = root->FirstChildElement();
			     child != nullptr; child = child->NextSiblingElement())
			{
				std::string s = child->Name();
				std::transform(s.begin(), s.end(), s.begin(), tolower);
				size_t keyHash = std::hash<std::string>()(s);

				// get the node name attrubte
				//const char* name = child->FirstChildElement();// ->Attribute("name");
				const char* ptrName = child->Attribute("name");

				if (ptrName == NULL && keyHash != SHADER_HASH)
				{
					std::cout << child->Name() << "Warning: ignoring unnamed node." << std::endl;
					continue;
				}

				// Parse node value

				if (keyHash == SHADER_HASH)
				{
					shaderCount++;
					ptrMaterial->setShader(
						resources::ResourceManager::get<graphics::Shader>(child->GetText()));
				}
				else if (keyHash == TEXTURE_HASH)
				{
					ptrMaterial->addTexture(
						ptrName,
						resources::ResourceManager::get<graphics::Texture>(child->GetText()));
				}
				else if (keyHash == CUBEMAP_HASH)
				{
					ptrMaterial->addCubeMap(
						ptrName,
						resources::ResourceManager::get<graphics::CubeMap>(child->GetText()));
				}
				else if (keyHash == VECTOR4_HASH)
				{
					std::stringstream input(child->GetText());
					glm::vec4 vec;
					input >> vec.x;
					input >> vec.y;
					input >> vec.z;
					input >> vec.w;

					ptrMaterial->addVec4(ptrName, vec);
				}
				else if (keyHash == VECTOR3_HASH)
				{
					std::stringstream input(child->GetText());
					glm::vec3 vec;
					input >> vec.x;
					input >> vec.y;
					input >> vec.z;
					ptrMaterial->addVec3(ptrName, vec);
				}
				else if (keyHash == VECTOR2_HASH)
				{
					std::stringstream input(child->GetText());
					glm::vec2 vec;
					input >> vec.x;
					input >> vec.y;

					ptrMaterial->addVec2(ptrName, vec);
				}
				else if (keyHash == FLOAT_HASH)
				{
					float value = 0;
					if (child->QueryFloatText(&value) != tinyxml2::XML_SUCCESS)
						std::cout << ptrName << ":" << " invlid float value '" << child->GetText() << "'" << std::endl;
					else
						ptrMaterial->addFloat(ptrName, value);
				}
				else if (keyHash == INT_HASH)
				{
					int value = 0;
					if (child->QueryIntText(&value) != tinyxml2::XML_SUCCESS)
						std::cout << ptrName << ":" << " invlid int value '" << child->GetText() << "'" << std::endl;
					else
						ptrMaterial->addInt(ptrName, value);
				}
				
			}

			// make sure this material has exactly ONE shader
			if (shaderCount == 0)
			{
				std::cout << "Error: No shader defined for this material!" << std::endl;
				delete ptrMaterial;
				return nullptr;
			}
			else if (shaderCount > 1)
			{
				std::cout << "Error: Multiple shaders defined for this material." << std::endl;
				delete ptrMaterial;
				return nullptr;
			}

			//std::cout << "Material loaded..." << std::endl;
			return ptrMaterial;
		}
	}
}
