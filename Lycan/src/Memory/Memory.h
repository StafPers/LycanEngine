#pragma once

#include "Core.h"

namespace Lycan
{
	namespace Memory
	{
		void MemoryCopy( void* _pDest, void* _pSrc, size_t _size )
		{
			char* pDest = reinterpret_cast< char* >( _pDest );
			char* pSrc  = reinterpret_cast< char* >( _pSrc );
			const char* const pEnd = pDest + _size;

			while( pDest != pEnd )
				*pDest++ = *pSrc++;
		}

		void MemorySet( void* _pDest, char _val, size_t _size )
		{
			char* pDest = reinterpret_cast< char* >( _pDest );
			const char* const pEnd = pDest + _size;

			while( pDest != pEnd )
				*pDest++ = _val;
		}
	}
}