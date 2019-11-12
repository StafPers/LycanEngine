#pragma once

#include "../Core/Core.h"

#include <math.h>

namespace Lycan
{
	namespace Math
	{
		constexpr double PI  = 3.14159265359f;
		constexpr double TAU = 6.28318530717f;

		template<typename T>
		T RadToDeg( T _rad ) { return _rad * ( T )180 / ( T )PI; }

		template<typename T>
		T DegToRad( T _deg ) { return _deg / ( T )180 * ( T )PI; }

		template<typename T>
		T InterpolateLinear( T _start, T _end, float _fraction )
		{
			return T( ( float )_start + ( ( ( float )_end - ( float )_start ) * _fraction ) );
		}

		template<typename T>
		T InterpolateCos( T _start, T _end, float _fraction )
		{
			const float cos_fraction = ( 1.0f - cosf( ( float )PI * _fraction ) ) * 0.5f;
			return interpolateLinear( _start, _end, cos_fraction );;
		}

		template< typename T >
		T Min( T _a, T _b )
		{
			return _a < _b ? _a : _b;
		}

		template< typename T >
		T Max( T _a, T _b )
		{
			return _a > _b ? _a : _b;
		}

		template< typename T >
		int Sign( T _val )
		{
			return ( _val > T( 0 ) ) - ( _val < T( 0 ) );
		}
		
		template< typename T >
		T Abs( T _val )
		{
			return _val * static_cast< T >( Sign( _val ) );
		}

		template< typename T >
		T Clamp( T _min, T _max, T _val )
		{
			return ( ( _val < _min ) ? _min : ( ( _val > _max ) ? _max : _val ) );
		}
	}
}