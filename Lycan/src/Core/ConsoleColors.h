#pragma once

#include "Core.h"

#include <Windows.h> // Prob do something about this

namespace Lycan
{
	namespace Core
	{
		enum LYCAN_API eConsoleColors
		{
			White        = FOREGROUND_BLUE  | FOREGROUND_RED | FOREGROUND_GREEN,
			LightRed     = FOREGROUND_RED   | FOREGROUND_INTENSITY,
			DarkRed      = FOREGROUND_RED,
			LightGreen   = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			DarkGreen    = FOREGROUND_GREEN,
			LightBlue    = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
			DarkBlue     = FOREGROUND_BLUE,
			LightYellow  = FOREGROUND_GREEN | FOREGROUND_RED  | FOREGROUND_INTENSITY,
			DarkYellow   = FOREGROUND_GREEN | FOREGROUND_RED,
			LightMagenta = FOREGROUND_BLUE  | FOREGROUND_RED  | FOREGROUND_INTENSITY,
			DarkMagenta  = FOREGROUND_BLUE  | FOREGROUND_RED,
			LightCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			DarkCyan     = FOREGROUND_BLUE  | FOREGROUND_GREEN
		};
	}
}