#include "time.h"
#include <assert.h>
#include "octoengine.h"

namespace octo {
	namespace core {

#define __TIME_INITIALIZATION_ASSERTION__ OCTO_ASSERT( (Time::m_Instance != nullptr), "Time class was not initialized")
#define MILISECOND 0.001
#define MICROSECOND 0.000001
#define NANOSECOND 0.000000001

		Time*  Time::m_Instance = nullptr;

		Time::Time()
			: m_TimeScale(0),
			m_FrameDeltaTime(0),
			m_GameStartTime(std::chrono::high_resolution_clock::now())
		{

		}

		Time::~Time()
		{
		}

		void Time::initialize()
		{
			Time::m_Instance = new Time();
		}

		void Time::destroy()
		{
			delete Time::m_Instance;
		}

		long long Time::getElapsedRealTime()
		{
			__TIME_INITIALIZATION_ASSERTION__
				auto now = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_Instance->m_GameStartTime).count();
		}

		long long Time::getElapsedGameTime()
		{
			__TIME_INITIALIZATION_ASSERTION__
				return 0;
		}

		void Time::setFrameStartTime()
		{
			__TIME_INITIALIZATION_ASSERTION__
				Time::m_Instance->m_FrameStartTime = std::chrono::high_resolution_clock::now();
		}

		void Time::setFrameEndTime()
		{
			__TIME_INITIALIZATION_ASSERTION__
				Time::m_Instance->m_FrameEndTime = std::chrono::high_resolution_clock::now();

			//return std::chrono::duration_cast<std::chrono::nanoseconds>(m_Instance->m_FrameEndTime - m_Instance->m_FrameStartTime).count() * NANOSECOND;
			//return std::chrono::duration_cast<std::chrono::microseconds>(m_Instance->m_FrameEndTime - m_Instance->m_FrameStartTime).count() * MICROSECOND;
			//return std::chrono::duration_cast<std::chrono::milliseconds>(m_Instance->m_FrameEndTime - m_Instance->m_FrameStartTime).count() * MILISECOND;

			Time::m_Instance->m_FrameDeltaTime =
				std::chrono::duration_cast<std::chrono::milliseconds>(m_Instance->m_FrameEndTime - m_Instance->m_FrameStartTime).count() * MILISECOND;

		}

		double Time::getDeltaTime()
		{
			__TIME_INITIALIZATION_ASSERTION__
				return Time::m_Instance->m_FrameDeltaTime;
		}

	}
}