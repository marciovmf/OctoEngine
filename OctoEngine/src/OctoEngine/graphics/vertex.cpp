#include "vertex.h"

namespace octo {
	namespace graphics {

		Vertex::Vertex()
		{}

		Vertex::Vertex(const glm::vec3& vertex):
			vertex(vertex){}
		
		Vertex::Vertex(const glm::vec3& vertex, const glm::vec3& color):
			vertex(vertex), color(color){}

		Vertex::Vertex(const glm::vec3& vertex, const glm::vec3& color, const glm::vec2& texCoord):
			vertex(vertex), color(color){}

		Vertex::Vertex(const glm::vec3& vertex, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal):
			vertex(vertex), color(), normal(normal), texCoord(texCoord){}

		Vertex::~Vertex()
		{}

	}
}