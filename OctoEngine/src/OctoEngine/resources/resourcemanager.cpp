#include "resourcemanager.h"
#include "tinyxml2.h"
#include "../graphics/shader.h"

#include <SOIL.h>
#include "../graphics/texture.h"
#include "../graphics/material.h"
#include <algorithm>
#include <sstream>

using namespace tinyxml2;

namespace octo {
	namespace resources {

		ResourceManager* ResourceManager::m_Instance = nullptr;

		ResourceManager::ResourceManager(){ }

		void ResourceManager::initialize() 
		{
			ResourceManager::m_Instance = new ResourceManager();
		}

		void ResourceManager::Destroy()
		{
			delete ResourceManager::m_Instance;
		}

		bool ResourceManager::ReleaseResource(ResourcePtr& resourcePtr)
		{
			
			if (ResourceManager::m_Instance->m_Resources.end() == 
				ResourceManager::m_Instance->m_Resources.find((*resourcePtr).getName()))
				return false;
			
			const char* name = resourcePtr->getName();
			resourcePtr.reset();
			if (ResourceManager::m_Instance->m_Resources[name].unique())
			{
				ResourceManager::m_Instance->m_Resources.erase(name);
				return true;
			}
			
			return false;
		}

		ResourceManager::~ResourceManager()
		{
			m_Loaders.clear();
			m_Resources.clear();
		}

		octo::resources::Resource* loadTexture(const char* resourceName)
		{
			int w = 0, h = 0;
			unsigned char* data = SOIL_load_image(resourceName, &w, &h, 0, SOIL_LOAD_RGBA);
			return new graphics::Texture(resourceName, data, w, h);
		}

		octo::resources::Resource* loadMaterial(const char* resourceName)
		{
			tinyxml2::XMLDocument xmlDoc;
			//std::cout << "Loading material '" << resourceName << "'" << std::endl;

			XMLError error = xmlDoc.LoadFile(resourceName);

			if (error != XMLError::XML_SUCCESS) {
				// TODO: Log that could not load the asset
				std::cout << "ERROR: Error loading xml file:" << error << std::endl;
				return nullptr;
			}

			XMLElement *root = xmlDoc.FirstChildElement("material");

			// Precalculate hash values for faster name comparing
			std::hash<std::string> strHash;
			size_t VECTOR4_HASH = strHash("vec4");
			size_t VECTOR3_HASH = strHash("vec3");
			size_t VECTOR2_HASH = strHash("vec2");
			size_t FLOAT_HASH = strHash("float");
			size_t INT_HASH = strHash("int");
			size_t SHADER_HASH = strHash("shader");
			size_t TEXTURE_HASH = strHash("texture");

			short int shaderCount = 0;

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
				const char *ptrName = child->Attribute("name");
				
				if ( ptrName == NULL && keyHash != SHADER_HASH)
				{
					std::cout << child->Name() << "Warning: ignoring unnamed node."<< std::endl;
					continue;
				} 

				//std::string elementName(ptrName);
				// Parse node value

				if (keyHash == SHADER_HASH)
				{
					shaderCount++;
					ptrMaterial->setShader(
						ResourceManager::get<graphics::Shader>(child->GetText()));
				}
				else if (keyHash == TEXTURE_HASH)
				{
					ptrMaterial->addTexture(
						ptrName,
						ResourceManager::get<graphics::Texture>(child->GetText()));
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
				else if (keyHash == VECTOR3_HASH )
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
					if (child->QueryFloatText(&value) != XML_SUCCESS)
						std::cout << ptrName << ":" << " invlid float value '" << child->GetText() << "'" << std::endl;
					else
						ptrMaterial->addFloat(ptrName, value);
				}
				else if (keyHash == INT_HASH)
				{
					int value = 0;
					if (child->QueryIntText(&value) != XML_SUCCESS)
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
			else if (shaderCount > 1 )
			{
				std::cout << "Error: Multiple shaders defined for this material." << std::endl;
				delete ptrMaterial;
				return nullptr;
			}

			//std::cout << "Material loaded..." << std::endl;
			return ptrMaterial;
		}

		octo::resources::Resource* loadMesh(const char* resourceName)
		{
			//throw new octo::Exception("Not implemented yet");
			return nullptr;
		}

		octo::resources::Resource* loadShader(const char* resourceName)
		{
			tinyxml2::XMLDocument xmlDoc;
			XMLError error = xmlDoc.LoadFile(resourceName);

			if (error != XMLError::XML_SUCCESS) {
				// TODO: Log that could not load the asset
				return nullptr;
			}

			XMLElement *ShaderElement = xmlDoc.FirstChildElement("SHADER");
			if (ShaderElement == nullptr)
				return false;

			XMLElement *vertexElement = ShaderElement->FirstChildElement("VERTEX");
			XMLElement *fragmentElement = ShaderElement->FirstChildElement("FRAGMENT");
			//XMLElement *GeometryElement = ShaderElement->FirstChildElement("GEOMETRY");
			XMLElement *capabilityElement = ShaderElement->FirstChildElement("CAPABILITY");

			if (vertexElement == nullptr || fragmentElement == nullptr)
				return nullptr;



			return new octo::graphics::Shader(resourceName, vertexElement->GetText(), fragmentElement->GetText());
		}
	}
}