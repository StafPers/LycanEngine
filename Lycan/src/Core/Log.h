#pragma once

#include "ConsoleColors.h"
#include "String.h"

namespace Lycan
{
	namespace Core
	{
		void LYCAN_API LogError  ( const String& _error );
		void LYCAN_API LogWarning( const String& _warning );
		void LYCAN_API LogMessage( const String& _message );
		void LYCAN_API LogMessage( const String& _message, eConsoleColors _color );
	}
}