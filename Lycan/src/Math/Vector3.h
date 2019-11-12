#pragma once

#include "../Core/Core.h"

namespace Lycan
{
	namespace Math
	{
		class LYCAN_API Vector3
		{
		public:
			Vector3                         ( void );
			Vector3                         ( float _x, float _y, float _z );

			inline float   SqrMagnitude     ( void ) const { return ( x * x ) + ( y * y ) + ( z * z ); }

			static float   DotProduct       ( const Vector3& _a, const Vector3& _b );
			static float   DeltaAngleRad    ( const Vector3& _a, const Vector3& _b );
			static float   DeltaAngleDeg    ( const Vector3& _a, const Vector3& _b );
			static float   Distance         ( const Vector3& _a, const Vector3& _b );
			static Vector3 CrossProduct     ( const Vector3& _a, const Vector3& _b );

			float          Magnitude        ( void )                const;
			void           Normalize        ( void );
			Vector3        Normalized       ( void )                const;

			Vector3        operator +       ( const Vector3& _rhs ) const;
			Vector3&       operator +=      ( const Vector3& _rhs );
			Vector3        operator +       ( float _rhs )          const;
			Vector3&       operator +=      ( float _rhs );

			Vector3        operator -       ( const Vector3& _rhs ) const;
			Vector3&       operator -=      ( const Vector3& _rhs );
			Vector3        operator -       ( float _rhs )          const;
			Vector3&       operator -=      ( float _rhs );

			Vector3        operator *       ( const Vector3& _rhs ) const;
			Vector3&       operator *=      ( const Vector3& _rhs );
			Vector3        operator *       ( float _rhs )          const;
			Vector3&       operator *=      ( float _rhs );

			bool           operator ==      ( const Vector3& _rhs ) const;
			bool           operator !=      ( const Vector3& _rhs ) const;

			static const Vector3 xHat;
			static const Vector3 yHat;
			static const Vector3 zHat;
			static const Vector3 zero;

			float x;
			float y;
			float z;
		};
	}
}
