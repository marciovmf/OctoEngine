#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace octo {
	namespace graphics {

		struct Vertex
		{
			glm::vec3 vertex;
			glm::vec3 color;
			glm::vec3 normal;
			glm::vec2 texCoord;

			Vertex();
			Vertex(const glm::vec3& vertex);
			Vertex(const glm::vec3& vertex, const glm::vec3& color);
			Vertex(const glm::vec3& vertex, const glm::vec3& color, const glm::vec2& texCoord);
			Vertex(const glm::vec3& vertex, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal);
			~Vertex();
		private:
		};
	}
}

