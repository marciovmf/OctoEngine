#include "cubemap.h"
#include "tinyxml2.h"
#include <SOIL.h>
#include <algorithm>
#include <sstream>

namespace octo {
	namespace graphics {


		CubeMapData::CubeMapData():
			front(nullptr), back(nullptr), up(nullptr), down(nullptr), left(nullptr), right(nullptr)
		{ }

		CubeMapData::~CubeMapData()
		{
			delete front;
			delete back;
			delete left;
			delete right;
			delete up;
			delete down;
		}

		CubeMap::CubeMap(const char* reosourceId, const CubeMapData* cubeMapData)
			: octo::resources::Resource(reosourceId), m_CubeMapData(cubeMapData)			
		{

			glGenTextures(1, &m_CubeMapId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapId);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->right);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->left);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->up);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->down);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->back);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, cubeMapData->width, cubeMapData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMapData->front);
			

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}


		CubeMap::~CubeMap()
		{	
			delete m_CubeMapData;
		}

		octo::resources::Resource* CubeMap::load(const char* resourceName)
		{
			//int w = 0, h = 0;
			//unsigned char* data = SOIL_load_image(resourceName, &w, &h, 0, SOIL_LOAD_RGBA);
			//return new graphics::CubeMap(resourceName,   );

			tinyxml2::XMLDocument xmlDoc;
			//std::cout << "Loading material '" << resourceName << "'" << std::endl;

			tinyxml2::XMLError error = xmlDoc.LoadFile(resourceName);

			if (error != tinyxml2::XMLError::XML_SUCCESS)
			{
				// TODO: Log that could not load the asset
				std::cout << "ERROR: Error loading cubemap file:" << error << std::endl;

				//TODO: Provide an empty cubemap to prevent exceptions here!
				return nullptr;
			}

			tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("cubemap");

			// Precalculate hash values for faster name comparing
			std::hash<std::string> strHash;
			const size_t FRONT_HASH = strHash("front");
			const size_t BACK_HASH = strHash("back");
			const size_t BOTTOM_HASH = strHash("bottom");
			const size_t UP_HASH = strHash("up");
			const size_t DOWN_HASH = strHash("down");
			const size_t LEFT_HASH = strHash("left");
			const size_t RIGHT_HASH = strHash("right");

			// Pointers for image data
			CubeMapData* cubemapData = new CubeMapData();

			int w, h;

			for (tinyxml2::XMLElement* child = root->FirstChildElement();
				child != nullptr; child = child->NextSiblingElement())
			{

				std::string s = child->Name();
				std::transform(s.begin(), s.end(), s.begin(), tolower);
				size_t keyHash = std::hash<std::string>()(s);

				// Load the cubemap images
				if (keyHash == FRONT_HASH)
				{
					cubemapData->front = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else if (keyHash == BACK_HASH)
				{
					cubemapData->back = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else if (keyHash == LEFT_HASH)
				{
					cubemapData->left = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else if (keyHash == RIGHT_HASH)
				{
					cubemapData->right = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else if (keyHash == UP_HASH)
				{
					cubemapData->up = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else if (keyHash == DOWN_HASH)
				{
					cubemapData->down = SOIL_load_image(child->GetText(), &w, &h, 0, SOIL_LOAD_RGBA);
				}
				else
				{
					continue;
				}

			}

			// Since all width and height must be tha same, just take the size of the last image loaded
			cubemapData->width = w;
			cubemapData->height = h;
			
			// Creates an empty material instance
			return new octo::graphics::CubeMap(resourceName, cubemapData);

		}
	}
}