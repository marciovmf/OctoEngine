#pragma once

#include <chrono>

namespace octo {
	namespace core {

		class Time
		{
		private:
			std::chrono::system_clock::time_point m_GameStartTime;
			std::chrono::system_clock::time_point m_FrameStartTime;
			std::chrono::system_clock::time_point m_FrameEndTime;
			std::chrono::system_clock::time_point m_LastUpdateTime;
			double m_DeltaTime;
			double m_TimeScale;

			static Time* m_Instance;

		private:
			Time();
			~Time();

		public: // public static methods
			// Gets the instance of this singleton
			static Time& getInstance();
			// Destroy the instance of this singleton
			static void destroy();

		public:
			// Updates the Engime clock
			void update();
			// Returns the time in seconds it took to complete the last frame
			double getDeltaTime();
			double getElapsedRealTime();
			double getElapsedGameTime();

			/*Sets the scale at which the game time is passing.
			If scale is set to 0.0 the game is basically paused if all your functions are frame rate independent.
			If scale is set to 1.0 the time is passing as fast as realtime.
			Setting values between 0.0 and 1.0, will make game time passes that much slower than realtime.
			*/
			void setTimeScale(double scale);
			double getTimeScale();

		};

	}
}
