#pragma once

#include "Core.h"

namespace Lycan
{
	namespace Core
	{
		class LYCAN_API LoopTimer
		{
		public:

			LoopTimer            ( float _target, float _time = 0.0f );

			void         Update  ( float _deltaTime );

			inline float Time    ( void ) const { return m_time; }
			inline float Fraction( void ) const { return m_time / m_target; }

		private:

			float m_target;
			float m_time;

		};
	}
}
