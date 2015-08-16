#pragma once

#include "window.h"
#include <string>

namespace octo {

	namespace core {

		class Game;

		class GameEngine
		{
		private:
			Window* m_Window;
		public:

			// Core methods
			GameEngine();
			~GameEngine();
			void run(int width, int height, std::string title, Game& game);

			// Window facade methods

				inline int getWindowWidth() const { return m_Window->getWidth(); }
			inline int getWindowHeight() const { return m_Window->getHeight(); }
		};
	}
}
