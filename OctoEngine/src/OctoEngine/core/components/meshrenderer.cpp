#include "meshrenderer.h"
#include "../../graphics/mesh.h"
#include "../../graphics/shader.h"
#include "../../graphics/material.h"
#include "../../core/gameobject.h"
#include "../../graphics/rendersettings.h"
#include <glm/glm.hpp>
#include <iostream>

namespace octo
{
	namespace core
	{
		MeshRenderer::MeshRenderer(std::shared_ptr<graphics::Material> material, graphics::Mesh* mesh)
			: IRenderer(), m_Material(material), m_Mesh(mesh)
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

		std::shared_ptr<graphics::Material> MeshRenderer::getMaterial()
		{
			return m_Material;
		}

		void MeshRenderer::render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
		{
			//std::cout << "Drawing: " << this->gameObject->getName().c_str() << std::endl;

			// pass material's uniforms to the shader
			m_Material->bind();

			auto shader = m_Material->getShader();

			// Update teh default uniforms
			shader->setUniform("modelMatrix", gameObject->getTransform().getTransformationMatrix());
			shader->setUniform("viewMatrix", viewMatrix);
			shader->setUniform("projectionMatrix", projectionMatrix);
			shader->setUniform("ambientLight", graphics::RenderSettings::AmbientLightColor);

			// Render the mesh
			m_Mesh->Render();

			m_Material->unbind();
		}
	}
}
