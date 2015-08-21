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
			double m_FrameDeltaTime;
			double m_TimeScale;

			static Time* m_Instance;
			Time();
			~Time();

			// public static methods
		public:
			static void initialize();
			static void destroy();
			static long long getElapsedRealTime();
			static long long getElapsedGameTime();

			// Returns the time in seconds it took to complete the last frame
			static double getDeltaTime();

			static void setFrameStartTime();
			static void setFrameEndTime();
			static void setTimeScale(double scale);
			static double getTimeScale();
		};

	}
}
