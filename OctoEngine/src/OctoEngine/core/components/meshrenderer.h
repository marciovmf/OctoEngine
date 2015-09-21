#pragma once

#include <memory>
#include "IRenderer.h"


namespace octo{
	namespace graphics {
		class Shader;
		class Material;
		class Mesh;
	}

	namespace core {

		class MeshRenderer : public IRenderer
		{
		private:
			std::shared_ptr<graphics::Material> m_Material;
			graphics::Mesh* m_Mesh;

		public:
			MeshRenderer(std::shared_ptr<graphics::Material> material, graphics::Mesh* mesh);
			void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;
			void setMesh(graphics::Mesh* mesh);
			graphics::Mesh& getMesh();
			//void setShader(graphics::Shader* shader);
			std::shared_ptr<graphics::Material> getMaterial();
		};
	}
}

