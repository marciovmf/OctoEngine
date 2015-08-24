
#define GLM_FORCE_RADIANS 1

#include <OctoEngine/core/gameengine.h>
#include "TestGame.h"
#include <OctoEngine/core/time.h>

int main(int argc, char** argv)
{
	octo::core::GameEngine* engine = new octo::core::GameEngine();
	TestGame* game = new TestGame();

	//Second monitor - FullScreen - 1920 x 1080
	//engine->run(1920, 1080, "OctoEngine test game", *game, 1);
	// Windowed - 800 x 600
	engine->run(800, 680, "OctoEngine test game", *game);

	delete engine;
	delete game;
	return 0;
}

