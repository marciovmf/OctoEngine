#include "meshrenderer.h"
#include "../../graphics/mesh.h"
#include "../../graphics/shader.h"
#include "../../core/gameobject.h"
#include <glm/glm.hpp>

namespace octo{
	namespace core {
		MeshRenderer::MeshRenderer(octo::graphics::Shader* shader, octo::graphics::Mesh* mesh)
			: Component(), m_Shader(shader), m_Mesh(mesh)
		{
		}

		void MeshRenderer::setMesh(octo::graphics::Mesh* mesh)
		{
			m_Mesh = mesh;
		}

		octo::graphics::Mesh& MeshRenderer::getMesh()
		{
			return *m_Mesh;
		}

		void MeshRenderer::setShader(octo::graphics::Shader* shader)
		{
			m_Shader = shader;
		}

		octo::graphics::Shader& MeshRenderer::getShader()
		{
			return *m_Shader;
		}

		void MeshRenderer::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
		{
			m_Shader->bind();

			// Update uniforms
			m_Shader->setUniform("modelMatrix", gameObject->getTransform().getTransformationMatrix());
			m_Shader->setUniform("viewMatrix", viewMatrix);
			m_Shader->setUniform("projectionMatrix", projectionMatrix);
			// Render the mesh
			m_Mesh->Render();

			m_Shader->unbind();
		}
	}
}