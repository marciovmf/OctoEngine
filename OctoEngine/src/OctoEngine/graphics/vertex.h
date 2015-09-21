#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace octo {
	namespace graphics {

		struct Vertex
		{
			glm::vec3 vertex;
			glm::vec3 normal;
			glm::vec2 texCoord;

			Vertex();
			Vertex(const glm::vec3& vertex);
			Vertex(const glm::vec3& vertex, const glm::vec2& texCoord);
			Vertex(const glm::vec3& vertex, const glm::vec3& normal);
			Vertex(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec2& texCoord);			
			Vertex(float vertexX, float vertexY, float vertexZ);
			Vertex(float vertexX, float vertexY, float vertexZ, float normalX, float normalY, float normalZ);
			Vertex(float vertexX, float vertexY, float vertexZ, float normalX, float normalY, float normalZ, float U, float V);
			Vertex(float vertexX, float vertexY, float vertexZ, float U, float V);
			~Vertex();

			inline const glm::vec3& getVertex() { return vertex;  }
			inline const glm::vec3& getNormal() { return normal; }
			inline const glm::vec2& getTextureCoord() { return texCoord; }

		private:

		};
	}
}

