#pragma once

#include <math.h>

namespace Lycan
{
	namespace Math
	{
		constexpr double PI  = 3.14159265359f;
		constexpr double TAU = 6.28318530717f;

		inline float  RadToDeg( float _rad )  { return _rad * 180.0f / ( float )PI; }
		inline double RadToDeg( double _rad ) { return _rad * 180.0 / PI; }

		inline float  DegToRad( float _deg )  { return _deg / 180.0f * ( float )PI; }
		inline double DegToRad( double _deg ) { return _deg / 180.0 * PI; }

		template<typename T>
		inline T InterpolateLinear( T _start, T _end, float _fraction )
		{
			return _start + ( ( _end - _start ) * _fraction );
		}

		template<typename T>
		inline T InterpolateCos( T _start, T _end, float _fraction )
		{
			const float cos_fraction = ( 1.0f - cosf( ( float )PI * _fraction ) ) * 0.5f;
			return interpolateLinear( _start, _end, cos_fraction );;
		}

		template< typename T >
		inline T Min( T _a, T _b )
		{
			return _a < _b ? _a : _b;
		}

		template< typename T >
		inline T Max( T _a, T _b )
		{
			return _a > _b ? _a : _b;
		}

		template< typename T >
		inline int Sign( T _val )
		{
			return ( _val > T( 0 ) ) - ( _val < T( 0 ) );
		}
		
		template< typename T >
		inline T Abs( T _val )
		{
			return _val * static_cast< T >( Sign( _val ) );
		}

		template< typename T >
		inline T Clamp( T _min, T _max, T _val )
		{
			return ( ( _val < _min ) ? _min : ( ( _val > _max ) ? _max : _val ) );
		}
	}
}