#pragma once

#ifdef LC_PLATFORM_WINDOWS
	#ifdef LC_BUILD_DLL
		#define LYCAN_API __declspec( dllexport )
	#else
		#define LYCAN_API __declspec( dllimport )
	#endif
#else
	#error Lycan only supports Windows
#endif