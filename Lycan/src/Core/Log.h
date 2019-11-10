#pragma once

#include "ConsoleColors.h"
#include "Core.h"
#include "String.h"

#include <stdio.h>
#include <Windows.h> 

namespace Lycan
{
	namespace Core
	{
		LYCAN_API void LogError( const String& _error )
		{
			HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
			WORD currentAttrib;
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
				currentAttrib = csbi.wAttributes;

			SetConsoleTextAttribute( hConsole, eConsoleColors::LightRed );
			printf( _error.CString() );
			SetConsoleTextAttribute( hConsole, currentAttrib );
		}
		
		LYCAN_API void LogWarning( const String& _warning )
		{
			HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
			WORD currentAttrib;
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
				currentAttrib = csbi.wAttributes;

			SetConsoleTextAttribute( hConsole, eConsoleColors::LightYellow );
			printf( _warning.CString() );
			SetConsoleTextAttribute( hConsole, currentAttrib );
		}
		
		LYCAN_API void  LogMessage( const String& _message )
		{
			printf( _message.CString() );
		}

		LYCAN_API void  LogMessage( const String& _message, eConsoleColors _color )
		{
			HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
			WORD currentAttrib;
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
				currentAttrib = csbi.wAttributes;

			SetConsoleTextAttribute( hConsole, _color );
			printf( _message.CString() );
			SetConsoleTextAttribute( hConsole, currentAttrib );
		}
	}
}