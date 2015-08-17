#pragma once
#include "component.h"


namespace octo{
	namespace graphics {
		class Shader;
		class Mesh;
	}

	namespace core {

		class MeshRenderer : public Component
		{
		private:
			graphics::Shader* m_Shader;
			graphics::Mesh* m_Mesh;

		public:
			MeshRenderer(graphics::Shader* shader, graphics::Mesh* mesh);
			void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix) override;
			void setMesh(graphics::Mesh* mesh);
			graphics::Mesh& getMesh();
			void setShader(graphics::Shader* shader);
			graphics::Shader& getShader();
		};
	}
}

