
#define GLM_FORCE_RADIANS 1

#include <OctoEngine/core/gameengine.h>
#include "TestGame.h"

int main(int argc, char** argv)
{
	octo::core::GameEngine* engine = new octo::core::GameEngine();
	TestGame* game = new TestGame();

	engine->run(800, 600, "OctoEngine test game", *game);

	delete engine;
	delete game;
	return 0;
}
