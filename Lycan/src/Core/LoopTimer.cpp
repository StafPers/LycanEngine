#include "LoopTimer.h"

namespace Lycan
{
	namespace Core
	{
		LoopTimer::LoopTimer( float _target, float _time )
			: m_target{ _target }
			, m_time{ _time }
		{}

		void LoopTimer::Update( float _deltaTime )
		{
			m_time += _deltaTime;
			while( m_time > m_target )
				m_time -= m_target;
		}
	}
}

