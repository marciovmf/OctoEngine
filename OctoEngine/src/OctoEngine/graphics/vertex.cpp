#include "vertex.h"

namespace octo {
	namespace graphics {

		Vertex::Vertex()
		{}

		Vertex::Vertex(const glm::vec3& vertex):
			vertex(vertex){}

		Vertex::Vertex(const glm::vec3& vertex, const glm::vec3& normal) :
			vertex(vertex), normal(normal), texCoord(glm::vec2(0,0))
		{			
		}

		Vertex::Vertex(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec2& texCoord) :
			vertex(vertex), normal(normal), texCoord(texCoord)
		{
		}

		Vertex::Vertex(const glm::vec3& vertex, const glm::vec2& texCoord) :
			vertex(vertex), texCoord(texCoord){}


		Vertex::Vertex(float vertexX, float vertexY, float vertexZ):
			vertex(glm::vec3(vertexX, vertexY, vertexZ)), normal(glm::vec3(0.0f, 0.0f, 0.0f)), texCoord(glm::vec2(0.0f, 0.0f))
		{
		}

		Vertex::Vertex(float vertexX, float vertexY, float vertexZ, float normalX, float normalY, float normalZ):
			vertex(glm::vec3(vertexX, vertexY, vertexZ)), normal(glm::vec3(normalX, normalY, normalZ)), texCoord(glm::vec2(0.0f, 0.0f))
		{
		}

		Vertex::Vertex(float vertexX, float vertexY, float vertexZ, float normalX, float normalY, float normalZ, float U, float V):
			vertex(glm::vec3(vertexX, vertexY, vertexZ)), normal(glm::vec3(normalX, normalY, normalZ)), texCoord(glm::vec2(U, V))
		{
		}

		Vertex::Vertex(float vertexX, float vertexY, float vertexZ, float U, float V):
			vertex(glm::vec3(vertexX, vertexY, vertexZ)), normal(glm::vec3(0.0f, 0.0f, 0.0f)), texCoord(glm::vec2(U, V))
		{
		}

		Vertex::~Vertex()
		{}

	}
}