#pragma once

#include "Core.h"
#include "Util.h"

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		inline void Swap( T& _rFirst, T& _rSecond )
		{
			const T temp = Move( _rFirst );
			_rFirst      = Move( _rSecond );
			_rSecond     = Move( temp );
		}

		size_t LYCAN_API NextPowerOfTwo( size_t _value );
	}
}