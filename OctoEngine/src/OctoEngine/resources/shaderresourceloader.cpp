#include "shaderresourceloader.h"
#include <tinyxml2.h>
#include "../graphics/shader.h"

using namespace tinyxml2;

namespace octo
{
	namespace resources
	{
		ShaderResourceLoader::ShaderResourceLoader():
			ResourceLoader()
		{
		}

		octo::resources::Resource* ShaderResourceLoader::loadResource(const char* resourceName)
		{
			XMLDocument xmlDoc;
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

		ShaderResourceLoader::~ShaderResourceLoader()
		{
		}
	}
}
