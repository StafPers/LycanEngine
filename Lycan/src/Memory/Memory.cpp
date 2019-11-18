#include "Memory.h"

void LYCAN_API Lycan::Memory::MemoryCopy( void * _pDest, void * _pSrc, size_t _size )
{
	char* pDest = reinterpret_cast< char* >( _pDest );
	char* pSrc  = reinterpret_cast< char* >( _pSrc );
	const char* const pEnd = pDest + _size;

	while( pDest != pEnd )
		*pDest++ = *pSrc++;
}

void LYCAN_API Lycan::Memory::MemorySet( void * _pDest, char _val, size_t _size )
{
	char* pDest = reinterpret_cast< char* >( _pDest );
	const char* const pEnd = pDest + _size;

	while( pDest != pEnd )
		*pDest++ = _val;

}

void LYCAN_API Lycan::Memory::MemorySet( void * _pDest, wchar_t _val, size_t _size )
{
	wchar_t* pDest = reinterpret_cast< wchar_t* >( _pDest );
	const wchar_t* const pEnd = pDest + _size;

	while( pDest != pEnd )
		*pDest++ = _val;
}
