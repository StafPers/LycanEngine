#pragma once

#include "Util.h"

#include <climits>

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		void Swap( T& _rFirst, T& _rSecond )
		{
			const T temp = Move( _rFirst );
			_rFirst    = Move( _rSecond );
			_rSecond   = Move( temp );
		}

		size_t NextPowerOfTwo( size_t _value )
		{
			--_value;
			for( size_t i = 1; i < sizeof( _value ) * CHAR_BIT; i *= 2 )
				_value |= _value >> i;

			++_value;
			return _value + static_cast< size_t >( _value == 0 );
		}
	}
}