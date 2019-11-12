#pragma once

#include "../Core/Core.h"

#include <math.h>

namespace Lycan
{
	namespace Math
	{
		constexpr double PI  = 3.14159265359f;
		constexpr double TAU = 6.28318530717f;

		float  RadToDeg( float _rad )  { return _rad * 180.0f / ( float )PI; }
		double RadToDeg( double _rad ) { return _rad * 180.0 / PI; }

		float  DegToRad( float _deg )  { return _deg / 180.0f * ( float )PI; }
		double DegToRad( double _deg ) { return _deg / 180.0 * PI; }

		float InterpolateLinear( float _start, float _end, float _fraction )
		{
			return ( _start + ( ( _end - _start ) * _fraction ) );
		}

		double InterpolateLinear( double _start, double _end, double _fraction )
		{
			return ( _start + ( ( _end - _start ) * _fraction ) );
		}

		float InterpolateCos( float _start, float _end, float _fraction )
		{
			const float cos_fraction = ( 1.0f - cosf( PI * _fraction ) ) * 0.5f;
			return InterpolateLinear( _start, _end, cos_fraction );;
		}

		double InterpolateCos( double _start, double _end, double _fraction )
		{
			const double cos_fraction = ( 1.0 - cos( PI * _fraction ) ) * 0.5;
			return InterpolateLinear( _start, _end, cos_fraction );;
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