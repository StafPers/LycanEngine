#pragma once

#include "../Core/Core.h"

namespace Lycan
{
	namespace Math
	{
		class LYCAN_API Vector2
		{
		public:
			Vector2                         ( void );
			Vector2                         ( float _x, float _y );

			inline float   SqrMagnitude     ( void ) const { return ( x * x ) + ( y * y ); }

			static float   DotProduct       ( const Vector2& _a, const Vector2& _b );
			static float   DeltaAngleRad    ( const Vector2& _a, const Vector2& _b );
			static float   DeltaAngleDeg    ( const Vector2& _a, const Vector2& _b );
			static float   Distance         ( const Vector2& _a, const Vector2& _b );
			static Vector2 InterpolateLinear( const Vector2& _start, const Vector2& _end, float _fraction );
			static Vector2 InterpolateCosine( const Vector2& _start, const Vector2& _end, float _fraction );
			static Vector2 Perpendicular    ( const Vector2& _v );

			float          Magnitude        ( void )                const;
			void           Normalize        ( void );
			Vector2        Normalized       ( void )                const;

			Vector2        operator +       ( const Vector2& _rhs ) const;
			Vector2&       operator +=      ( const Vector2& _rhs );
			Vector2        operator +       ( float _rhs )          const;
			Vector2&       operator +=      ( float _rhs );

			Vector2        operator -       ( const Vector2& _rhs ) const;
			Vector2&       operator -=      ( const Vector2& _rhs );
			Vector2        operator -       ( float _rhs )          const;
			Vector2&       operator -=      ( float _rhs );

			Vector2        operator *       ( const Vector2& _rhs ) const;
			Vector2&       operator *=      ( const Vector2& _rhs );
			Vector2        operator *       ( float _rhs )          const;
			Vector2&       operator *=      ( float _rhs );

			bool           operator ==      ( const Vector2& _rhs ) const;
			bool           operator !=      ( const Vector2& _rhs ) const;

			static const Vector2 xHat;
			static const Vector2 yHat;
			static const Vector2 zero;

			float x;
			float y;
		};
	}
}
