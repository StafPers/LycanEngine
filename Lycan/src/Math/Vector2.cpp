#include "Vector2.h"

#include "Math.h"

namespace Lycan
{
	namespace Math
	{
		const Vector2 Vector2::xHat = Vector2( 1.0f, 0.0f );
		const Vector2 Vector2::yHat = Vector2( 0.0f, 1.0f );
		const Vector2 Vector2::zero = Vector2( 0.0f, 0.0f );

		Vector2::Vector2( void )
			: x{ 0.0f }
			, y{ 0.0f }
		{}

		Vector2::Vector2( float _x, float _y )
			: x{ _x }
			, y{ _y }
		{}

		float Vector2::DotProduct( const Vector2& _a, const Vector2& _b )
		{
			return ( _a.x * _b.x ) + ( _a.y * _b.y );
		}

		float Vector2::DeltaAngleRad( const Vector2& _a, const Vector2& _b )
		{
			return acosf( DotProduct( _a.Normalized(), _b.Normalized() ) );
		}

		float Vector2::DeltaAngleDeg( const Vector2& _a, const Vector2& _b )
		{
			return Math::RadToDeg( DeltaAngleRad( _a, _b ) );
		}

		float Vector2::Distance( const Vector2& _a, const Vector2& _b )
		{
			return ( _b - _a ).Magnitude();
		}

		Vector2 Vector2::Perpendicular( const Vector2& _v )
		{
			return Vector2( _v.y, -_v.x );
		}

		float Vector2::Magnitude( void ) const
		{
			return sqrtf( SqrMagnitude() );
		}

		void Vector2::Normalize( void )
		{
			// TODO: Throw exception if *this == zero
			const float length = Magnitude();
			x /= length;
			y /= length;
		}

		Vector2 Vector2::Normalized( void ) const
		{
			// TODO: Throw exception if *this == zero
			const float length = Magnitude();
			return Vector2( x / length, y / length );
		}

		Vector2 Vector2::operator+( const Vector2& _rhs ) const
		{
			return Vector2( x + _rhs.x, y + _rhs.y );
		}

		Vector2& Vector2::operator+=( const Vector2& _rhs )
		{
			return *this = *this + _rhs;
		}

		Vector2 Vector2::operator+( float _rhs ) const
		{
			return Vector2( x + _rhs, y + _rhs );
		}

		Vector2& Vector2::operator+=( float _rhs )
		{
			return *this = *this + _rhs;
		}

		Vector2 Vector2::operator-( const Vector2& _rhs ) const
		{
			return Vector2( x - _rhs.x, y - _rhs.y );
		}

		Vector2& Vector2::operator-=( const Vector2& _rhs )
		{
			return *this = *this - _rhs;
		}

		Vector2 Vector2::operator-( float _rhs ) const
		{
			return Vector2( x - _rhs, y - _rhs );
		}

		Vector2& Vector2::operator-=( float _rhs )
		{
			return *this = *this - _rhs;
		}

		Vector2 Vector2::operator*( float _rhs ) const
		{
			return Vector2( x * _rhs, y * _rhs );
		}

		Vector2& Vector2::operator*=( float _rhs )
		{
			return *this = *this * _rhs;
		}

		bool Vector2::operator==( const Vector2& _rhs ) const
		{
			return x == _rhs.x && y == _rhs.y;
		}

		bool Vector2::operator!=( const Vector2& _rhs ) const
		{
			return !( *this == _rhs );
		}
	}
}
