#include "Util.h"

size_t LYCAN_API Lycan::Core::Strlen( const char* _str )
{
	size_t count = 0;
	for( size_t i = 0; _str[ i ] != 0; ++i, ++count );
	return count;
}

size_t LYCAN_API Lycan::Core::Strlen( const wchar_t* _str )
{
	size_t count = 0;
	for( size_t i = 0; _str[ i ] != 0; ++i, ++count );
	return count;
}
