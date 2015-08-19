#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <OctoEngine/core/game.h>

namespace octo {
	namespace graphics {
		class Shader;
		class Mesh;
	}

	namespace core {
		class Transform;
		class GameObject;
		class MeshRenderer;
		class Camera;
	}
}

class TestGame : public octo::core::Game
{
private:
	octo::graphics::Shader* m_Shader;
	octo::graphics::Mesh* m_Mesh;

	//octo::core::GameObject* m_GameObject1;
	//octo::core::GameObject* m_GameObject2;
	//octo::core::GameObject* m_GameObject3;
	//octo::core::GameObject* m_CameraGameObject;
	

	/*octo::core::MeshRenderer* m_meshRenderer1;
	octo::core::MeshRenderer* m_meshRenderer2;
	octo::core::MeshRenderer* m_meshRenderer3;*/

	//glm::mat4 m_ProjectionMatrix;
	//glm::mat4 m_ViewMatrix;

	octo::core::Camera* m_Camera;

public:
	TestGame();
	~TestGame();
	void OnStart() override;
	//void OnUpdate() override;
	void OnFinish() override;
};

