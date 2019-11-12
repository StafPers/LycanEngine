#include "Vector3.h"

#include "Math.h"

namespace Lycan
{
	namespace Math
	{
		const Vector3 Vector3::xHat = Vector3( 1.0f, 0.0f, 0.0f );
		const Vector3 Vector3::yHat = Vector3( 0.0f, 1.0f, 0.0f );
		const Vector3 Vector3::zHat = Vector3( 0.0f, 0.0f, 1.0f );
		const Vector3 Vector3::zero = Vector3( 0.0f, 0.0f, 0.0f );

		Vector3::Vector3( void )
			: x{ 0.0f }
			, y{ 0.0f }
			, z{ 0.0f }
		{}

		Vector3::Vector3( float _x, float _y, float _z )
			: x{ _x }
			, y{ _y }
			, z{ _z }
		{}

		float Vector3::DotProduct( const Vector3& _a, const Vector3& _b )
		{
			return ( _a.x * _b.x ) + ( _a.y * _b.y ) + ( _a.z * _a.z );
		}

		float Vector3::DeltaAngleRad( const Vector3& _a, const Vector3& _b )
		{
			return acosf( DotProduct( _a.Normalized(), _b.Normalized() ) );
		}

		float Vector3::DeltaAngleDeg( const Vector3& _a, const Vector3& _b )
		{
			return Math::RadToDeg( DeltaAngleRad( _a, _b ) );
		}

		float Vector3::Distance( const Vector3& _a, const Vector3& _b )
		{
			return ( _b - _a ).Magnitude();
		}

		Vector3 Vector3::CrossProduct( const Vector3& _a, const Vector3& _b )
		{
			return Vector3(
				( _a.y * _b.z ) - ( _a.z * _b.y ),
				( _a.z * _b.x ) - ( _a.x - _b.z ),
				( _a.x * _b.y ) - ( _a.y - _b.x )
			);
		}

		float Vector3::Magnitude( void ) const
		{
			return sqrtf( SqrMagnitude() );
		}

		void Vector3::Normalize( void )
		{
			// TODO: throw exception if *this == zero
			const float length = Magnitude();
			x /= length;
			y /= length;
			z /= length;
		}

		Vector3 Vector3::Normalized( void ) const
		{
			// TODO: throw exception if *this == zero
			const float length = Magnitude();
			return Vector3( x / length, y / length, z / length );
		}

		Vector3 Vector3::operator+( const Vector3& _rhs ) const
		{
			return Vector3( x + _rhs.x, y + _rhs.y, z + _rhs.z );
		}

		Vector3& Vector3::operator+=( const Vector3& _rhs )
		{
			return *this = *this + _rhs;
		}

		Vector3 Vector3::operator+( float _rhs ) const
		{
			return Vector3( x + _rhs, y + _rhs, z + _rhs );
		}

		Vector3& Vector3::operator+=( float _rhs )
		{
			return *this = *this + _rhs;
		}

		Vector3 Vector3::operator-( const Vector3& _rhs ) const
		{
			return Vector3( x - _rhs.x, y - _rhs.y, z - _rhs.z );
		}

		Vector3& Vector3::operator-=( const Vector3& _rhs )
		{
			return *this = *this - _rhs;
		}

		Vector3 Vector3::operator-( float _rhs ) const
		{
			return Vector3( x - _rhs, y - _rhs, z - _rhs );
		}

		Vector3& Vector3::operator-=( float _rhs )
		{
			return *this = *this - _rhs;
		}

		Vector3 Vector3::operator*( const Vector3& _rhs ) const
		{
			return Vector3( x * _rhs.x, y * _rhs.y, z * _rhs.z );
		}

		Vector3& Vector3::operator*=( const Vector3& _rhs )
		{
			return *this = *this * _rhs;
		}

		Vector3 Vector3::operator*( float _rhs ) const
		{
			return Vector3( x * _rhs, y * _rhs, z * _rhs );
		}

		Vector3& Vector3::operator*=( float _rhs )
		{
			return *this = *this * _rhs;
		}

		bool Vector3::operator==( const Vector3& _rhs ) const
		{
			return ( x == _rhs.x ) && ( y == _rhs.y ) && ( z == _rhs.z );
		}

		bool Vector3::operator!=( const Vector3& _rhs ) const
		{
			return !( *this == _rhs );
		}
	}
}
