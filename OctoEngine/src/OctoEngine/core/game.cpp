#include "game.h"
#include "gameengine.h"

namespace octo
{
	namespace core
	{
		//Game::Game(GameEngine &gameEngine)
		//	:engine(gameEngine)
		//{
		//}

		Game::Game() : engine(nullptr)
		{
		}

		Game::~Game()
		{
		}

		void Game::setEngine(GameEngine* engine)
		{
			this->engine = engine;
		}
	}
}
