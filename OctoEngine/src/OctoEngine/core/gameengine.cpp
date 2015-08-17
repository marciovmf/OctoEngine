#include "game.h"
#include "gameengine.h"

namespace octo {

	namespace core {

		GameEngine::GameEngine() 
			: m_Window(NULL)
		{ 
		}

		GameEngine::~GameEngine()
		{
			// clean up engine resources
			if (m_Window)
				delete m_Window;
		}

		void GameEngine::run(int width, int height, std::string title, Game& game)
		{
			// Give to the game a reference to this class
			game.setEngine(this);

			// Initialize the game window and the graphics system
			m_Window = new Window(width, height, title);
			// Setup viewport
			glViewport(0, 0, width, height);
			
			// Allows the game to make its own initializations
			game.OnStart();

			// Stars the main loop
			while (!m_Window->shouldClose())
			{
				m_Window->clear();
				game.OnUpdate();
				m_Window->update();
			}

			// Let the game do its own cleanup
			game.OnFinish();
		}
	}
}