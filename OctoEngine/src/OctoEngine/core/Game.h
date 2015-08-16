#pragma once

namespace octo {
	namespace core {

		class GameEngine;

		class Game
		{
		protected:
			GameEngine* engine;
		public:
			Game(/*GameEngine &gameEngine*/);
			virtual ~Game();

			/*This method is called by the engine before the first frame*/
			virtual void OnStart(){}

			/*This method is called once per frame*/
			virtual void OnUpdate(){}

			/*This method is called before the game finishes and before all resource cleanup*/
			virtual void OnFinish(){}

			void setEngine(GameEngine* engine);

		private:
			Game(const Game& other) = delete;
			void operator=(const Game& other) = delete;

		};
	}
}

