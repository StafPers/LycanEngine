#pragma once

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
			return static_cast< T&& >( Arg )
		}

		template< typename T >
		constexpr T&& Forward( typename RemoveReference< T >::type&& Arg ) noexcept
		{
			static_assert( !IsLvalueReference< T >::value, "Invalid rvalue to lvalue conversion" );
			return static_cast< T&& >( Arg );
		}
	}
}