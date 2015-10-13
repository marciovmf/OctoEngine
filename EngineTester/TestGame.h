#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <OctoEngine/core/game.h>

namespace octo
{
	namespace graphics
	{
		class Shader;
		class Mesh;
	}

	namespace core
	{
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
	octo::graphics::Mesh* m_boxMesh;
	octo::graphics::Mesh* m_planeMesh;
	octo::core::Camera* m_Camera;

public:
	TestGame();
	~TestGame();
	void OnStart() override;
	//void OnUpdate() override;
	void OnFinish() override;
};
