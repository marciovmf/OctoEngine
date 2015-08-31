#pragma once
#include "../core/octoengine.h"
#include "shader.h"
#include <memory>
#include <map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace octo
{
	namespace graphics
	{
		class Texture;

		class Material :
			public octo::resources::Resource
		{
		private:
			std::shared_ptr<Shader> m_Shader;
			std::map<std::string, float> m_FloatValues;
			std::map<std::string, int> m_IntValues;
			std::map<std::string, glm::vec4> m_Vec4Values;
			std::map<std::string, glm::vec3> m_Vec3Values;
			std::map<std::string, glm::vec2> m_Vec2Values;
			std::map<std::string, std::shared_ptr<graphics::Texture>> m_Textures;
		public:
			Material(const char* resourceName, std::shared_ptr<Shader> shaderResourcePtr);
			Material(const char* resourceName);
			void setShader(std::shared_ptr<Shader> shader);
			void addFloat(std::string name, float value);
			void addInt(std::string name, int value);
			void addVec3(std::string name, glm::vec3 value);
			void addVec4(std::string name, glm::vec4 value);
			void addVec2(std::string name, glm::vec2 value);
			void addTexture(std::string name, std::shared_ptr<Texture> textureResource);

			std::shared_ptr<Shader> getShader();
			float getFloat(const char* name);
			int getInt(const char* name);
			glm::vec4 getVec4(const char* name);
			glm::vec3 getVec3(const char* name);
			glm::vec2 getVec2(const char* name);
			void bind();
			void unbind();
			std::shared_ptr<graphics::Texture> getTexture(const char* name);
			~Material();
		};
	}
}
