#pragma once

#include "Core.h"

#include <stdio.h>

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		struct RemoveReference { typedef T type; };

		template< typename T >
		struct RemoveReference< T& > { typedef T type; };

		template< typename T >
		struct RemoveReference< T&& > { typedef T type; };

		template< typename T >
		constexpr typename RemoveReference< T >::type&& Move( T&& Arg ) noexcept
		{
			return static_cast< typename RemoveReference< T >::type&& >( Arg );
		}

		template< typename T > struct IsLvalueReference { static constexpr bool value = false; };
		template< typename T > struct IsLvalueReference< T& > { static constexpr bool value = true; };

		template< typename T >
		constexpr T&& Forward( typename RemoveReference< T >::type& Arg ) noexcept
		{
			return static_cast< T&& >( Arg );
		}

		template< typename T >
		constexpr T&& Forward( typename RemoveReference< T >::type&& Arg ) noexcept
		{
			static_assert( !IsLvalueReference< T >::value, "Invalid rvalue to lvalue conversion" );
			return static_cast< T&& >( Arg );
		}

		size_t LYCAN_API Strlen( const char* _str );
		size_t LYCAN_API Strlen( const wchar_t* _str );

		template< typename... Args >
		inline size_t StrFormat( wchar_t* _pDest, size_t _length, const wchar_t* _str, Args&&... _args )
		{
			return static_cast< size_t >( _snwprintf( _pDest, _length, _str, Forward< Args >( _args )... ) );
		}

		template< typename... Args >
		inline size_t StrFormat( char* _pDest, size_t _length, const char* _str, Args&&... _args )
		{
			return static_cast< size_t >( snprintf( _pDest, _length, _str, Forward< Args >( _args )... ) );
		}
	}
}