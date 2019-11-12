#include "LycanWin.h" 

#include "Clock.h"

namespace Lycan
{
	namespace Core
	{
		static __int64 PerformanceCounter( void )
		{
			LARGE_INTEGER li;
			::QueryPerformanceCounter( &li );
			return li.QuadPart;
		}

		static __int64 PerformanceFrequency( void )
		{
			LARGE_INTEGER li;
			::QueryPerformanceFrequency( &li );
			return li.QuadPart;
		}

		Clock::Clock( void )
			: m_deltaTime { 0.0f }
			, m_lifeTime  { 0.0 }
		    , m_mark      { PerformanceCounter() }
		{}

		Clock& Clock::Instance( void )
		{
			static Clock instance;
			return instance;
		}

		void Clock::Update( void )
		{
			const float counterDiff = static_cast< float >( PerformanceCounter() - m_mark );
			m_mark = PerformanceCounter();
			const float freq = static_cast< float >( PerformanceFrequency() );

			m_deltaTime = counterDiff / freq;
			m_lifeTime += m_deltaTime;
		}
	}
}
