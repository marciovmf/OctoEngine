#include "resourcemanager.h"
#include "tinyxml2.h"
#include "../graphics/shader.h"
#include "../core/exception/exception.h"

#include <SOIL.h>
#include "../graphics/texture.h"

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
			XMLError error = xmlDoc.LoadFile(resourceName);

			XMLElement *root = xmlDoc.FirstChildElement("MATERIAL");
			if (error != XMLError::XML_SUCCESS) {
				// TODO: Log that could not load the asset
				return nullptr;
			}

			XMLElement* e;
			while ( (e=root->NextSiblingElement()) != nullptr)
			{
				std::cout << e->Name() << " = " << e->GetText() << std::endl;
			}

			return nullptr;
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

			if (vertexElement == nullptr || fragmentElement == nullptr)
				return nullptr;

			return new octo::graphics::Shader(resourceName, vertexElement->GetText(), fragmentElement->GetText());
		}
	}
}