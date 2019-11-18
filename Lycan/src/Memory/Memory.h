#pragma once

#include "../Core/Core.h"

namespace Lycan
{
	namespace Memory
	{
		void LYCAN_API MemoryCopy( void* _pDest, void* _pSrc, size_t _size );
		void LYCAN_API MemorySet( void* _pDest, char _val, size_t _size );
		void LYCAN_API MemorySet( void* _pDest, wchar_t _val, size_t _size );


	
	}
}