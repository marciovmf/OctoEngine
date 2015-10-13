#include "time.h"
#include <assert.h>
#include "octoengine.h"
#include "exception/exception.h"

namespace octo
{
	namespace core
	{
#define MILISECOND 0.001


		//#define RESOLUTION nanoseconds
#define RESOLUTION milisseconds
#define IDEAL_FRAME_TIME 1.0/60.0

		Time* Time::m_Instance = nullptr;

		Time::Time()
			: m_TimeScale(1),
			  m_DeltaTime(IDEAL_FRAME_TIME),
			  m_GameStartTime(std::chrono::high_resolution_clock::now())
		{
		}

		Time::~Time()
		{
		}

		Time& Time::getInstance()
		{
			if (m_Instance == nullptr)
				m_Instance = new Time();
			return *m_Instance;
		}

		void Time::destroy()
		{
			delete m_Instance;
		}

		double Time::getElapsedRealTime()
		{
			auto now = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_Instance->m_GameStartTime).count() * MILISECOND;
		}

		double Time::getElapsedGameTime()
		{
			//TODO: Implement this, considering the timeScale;
			return -1;
		}

		void Time::update()
		{
			auto now = std::chrono::high_resolution_clock::now();

			//---------------------------
			//update the delta time
			//---------------------------
			m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
				now - m_LastUpdateTime).count() * MILISECOND * m_TimeScale;

#ifdef DEBUG
			// If the delta time is too big, this may indicate that we are returning from a breakpoint.
			// So, to keep things sane, frame-lock this frame time.
			if (m_DeltaTime > 1.0 / 10.0)
				m_DeltaTime = IDEAL_FRAME_TIME;
#endif


			m_LastUpdateTime = now;
		}

		void Time::setTimeScale(double scale)
		{
			m_Instance->m_TimeScale = scale;
		}

		double Time::getTimeScale()
		{
			return m_Instance->m_TimeScale;
		}

		double Time::getDeltaTime()
		{
			return m_DeltaTime;
		}
	}
}
