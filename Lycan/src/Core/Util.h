#pragma once

#include "Core.h"

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		struct LYCAN_API RemoveReference { typedef T type; };

		template< typename T >
		struct LYCAN_API RemoveReference< T& > { typedef T type; };

		template< typename T >
		struct LYCAN_API RemoveReference< T&& > { typedef T type; };

		template< typename T >
		LYCAN_API constexpr typename RemoveReference< T >::type&& Move( T&& Arg ) noexcept
		{
			return static_cast< typename RemoveReference< T >::type&& >( Arg );
		}

		template< typename T > struct LYCAN_API IsLvalueReference { static constexpr bool value = false; };
		template< typename T > struct LYCAN_API IsLvalueReference< T& > { static constexpr bool value = true; };

		template< typename T >
		LYCAN_API constexpr T&& Forward( typename RemoveReference< T >::type& Arg ) noexcept
		{
			return static_cast< T&& >( Arg )
		}

		template< typename T >
		LYCAN_API constexpr T&& Forward( typename RemoveReference< T >::type&& Arg ) noexcept
		{
			static_assert( !IsLvalueReference< T >::value, "Invalid rvalue to lvalue conversion" );
			return static_cast< T&& >( Arg );
		}
	}
}