#include "LycanWin.h" 

#include "Log.h"

#include <stdio.h>
#include <string>

void Lycan::Core::LogError( const String& _error )
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

void Lycan::Core::LogWarning( const String& _warning )
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

void Lycan::Core::LogMessage( const String& _message )
{
	printf( _message.CString() );
}

void Lycan::Core::LogMessage( const String& _message, eConsoleColors _color )
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

void LYCAN_API Lycan::Core::LogError( const WString& _error )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD currentAttrib;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
		currentAttrib = csbi.wAttributes;

	SetConsoleTextAttribute( hConsole, eConsoleColors::LightRed );
	wprintf( _error.CString() );
	SetConsoleTextAttribute( hConsole, currentAttrib );
}

void LYCAN_API Lycan::Core::LogWarning( const WString& _warning )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD currentAttrib;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
		currentAttrib = csbi.wAttributes;

	SetConsoleTextAttribute( hConsole, eConsoleColors::LightYellow );
	wprintf( _warning.CString() );
	SetConsoleTextAttribute( hConsole, currentAttrib );
}

void LYCAN_API Lycan::Core::LogMessage( const WString& _message )
{
	wprintf( _message.CString() );
}

void LYCAN_API Lycan::Core::LogMessage( const WString& _message, eConsoleColors _color )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD currentAttrib;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
		currentAttrib = csbi.wAttributes;

	SetConsoleTextAttribute( hConsole, _color );
	wprintf( _message.CString() );
	SetConsoleTextAttribute( hConsole, currentAttrib );
}
