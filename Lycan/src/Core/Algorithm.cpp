#include "Algorithm.h"

#include <climits>

size_t LYCAN_API Lycan::Core::NextPowerOfTwo( size_t _value )
{
	--_value;
	for( size_t i = 1; i < sizeof( _value ) * CHAR_BIT; i *= 2 )
		_value |= _value >> i;

	++_value;
	return _value + static_cast< size_t >( _value == 0 );
}
