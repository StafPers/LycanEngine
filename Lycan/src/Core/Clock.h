#pragma once

#include "Core.h"

namespace Lycan
{
	namespace Core
	{
		class LYCAN_API Clock
		{
		public:

			static Clock& Instance( void );

			void          Update    ( void );
			inline float  DeltaTime ( void ) const { return m_deltaTime; }
			inline double LifeTime  ( void ) const { return m_lifeTime; }

		private:

			Clock                   ( void );
			Clock                   ( const Clock& ) = delete;
			Clock& operator=        ( const Clock& ) = delete;

			float   m_deltaTime;
			double  m_lifeTime;
			__int64 m_mark;

		};
	}
}
