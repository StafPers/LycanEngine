#pragma once

namespace Lycan
{
	namespace Core
	{
		void MemoryCopy( void* _pDest, void* _pSrc, size_t _size )
		{
			char* pDest = reinterpret_cast< char* >( _pDest );
			char* pSrc  = reinterpret_cast< char* >( _pSrc );
			const char* const pEnd = pDest + _size;

			while( pDest != pEnd )
				*pDest++ = *pSrc++;
		}
	}
}