#include "mesh.h"
#include <iostream>

namespace octo {
	namespace graphics {

		Mesh::Mesh(const std::vector<Vertex>& vertices/*, const std::vector<GLuint>& indices*/)
			:m_Vertices(vertices) //, m_Indices(indices)
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			//glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(octo::graphics::Vertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

			// Vertices
			glEnableVertexAttribArray(RENDERER_VERTEX_INDEX);
			glVertexAttribPointer(RENDERER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(octo::graphics::Vertex), (const GLvoid*)offsetof(Vertex, vertex));

			// Normal
			glEnableVertexAttribArray(RENDERER_NORMAL_INDEX);
			glVertexAttribPointer(RENDERER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(octo::graphics::Vertex), (const GLvoid*)offsetof(Vertex, normal));

			// UVs
			glEnableVertexAttribArray(RENDERER_TEXCOORD_INDEX);
			glVertexAttribPointer(RENDERER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(octo::graphics::Vertex), (const GLvoid*)offsetof(Vertex, texCoord));


			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			// Indices
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER,				// Just an array of data
			//	m_Indices.size() * sizeof(GLuint),				// buffer size
			//	m_Indices.data(),								// pointer to the actual data
			//	GL_STATIC_DRAW);								// this data is static and will not be modified
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		Mesh::~Mesh()
		{
			//delete m_Vertices;
			//delete m_Indices;
		}

		void Mesh::Render() const
		{

			glBindVertexArray(m_VAO);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			//glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, NULL);
			glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}
	}
}