#pragma once

#include "Core.h"
#include "DynamicArray.h"

#include "Algorithm.h"
#include "../Memory/Memory.h"
#include "Util.h"

#include <stdio.h>

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		class GenericString
		{
		public:
			
			using IndexList  = DynamicArray< size_t >;
			using StringList = DynamicArray< GenericString< T > >;

			GenericString( void )
				: m_length   { 0 }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( 5 );
			}

			GenericString( const T* _pStr )
				: m_length   { Strlen( _pStr ) }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _pStr[ i ];
			}

			GenericString( T _c, size_t _count )
				: m_length   { _count }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );
				Memory::MemorySet( m_pBuffer, _c, _count );
			}

			GenericString( size_t _capactiy )
				: m_length   { 0 }
				, m_capacity { _capactiy }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_capacity );
			}

			template< typename... Args >
			GenericString( const T* _str, Args&&... _args )
				: m_length   { 0 }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				m_length = StrFormat( nullptr, 0, _str, Forward< Args >( _args )... );
				Reserve( m_length );
				StrFormat( m_pBuffer, m_length + 1, _str, Forward< Args >( _args )... );
			}

			GenericString( const GenericString< T >& _rSource )
				: m_length   { _rSource.m_length }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];
			}

			GenericString( GenericString< T >&& _rSource )
				: m_length   { _rSource.m_length }
				, m_capacity { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];

				_rSource.m_length   = 0;
				_rSource.m_capacity = 0;
				_rSource.m_pBuffer  = nullptr;
			}

			~GenericString( void )
			{
				delete[] m_pBuffer;
			}

			GenericString< T >& operator=( const GenericString< T >& _rSource )
			{
				if( &_rSource == this )
					return *this;

				m_length   = _rSource.m_length;
				m_capacity = m_length + 1;
				
				Reserve( m_capacity );

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];

				return *this;
			}

			GenericString< T >& operator=( GenericString< T >&& _rSource )
			{
				m_capacity = 0;
				m_length   = _rSource.m_length;
				Reserve( m_length );
				
				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];

				_rSource.m_length   = 0;
				_rSource.m_capacity = 0;
				_rSource.m_pBuffer  = nullptr;

				return *this;
			}

			GenericString< T > operator+( const GenericString< T >& _rhs ) const
			{
				GenericString< T > str = *this;
				return str.Append( _rhs );
			}

			GenericString< T >& operator+=( const GenericString< T >& _rhs )
			{
				return Append( _rhs );
			}

			const T& operator[]( size_t _index ) const
			{
				if( _index >= m_length )
				{
					// TODO: Throw exception
				}

				return m_pBuffer[ _index ];
			}

			T& operator[]( size_t _index )
			{
				if( _index >= m_length )
				{
					// TODO: Throw exception
				}

				return m_pBuffer[ _index ];
			}

			bool operator==( const GenericString< T >& _rhs ) const
			{
				if( m_length != _rhs.m_length )
					return false;

				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] != _rhs[ i ] )
						return false;

				return true;
			}

			bool operator!=( const GenericString< T >& _rhs ) const
			{
				return !( *this == _rhs );
			}

			// TODO: Might need overloads for const char* if they don't implicitly convert
			GenericString< T >& Append( const GenericString< T >& _rOther )
			{
				const size_t newLength = m_length + _rOther.m_length;
				Reserve( newLength );

				for( size_t i = m_length; i < newLength; ++i )
					m_pBuffer[ i ] = _rOther[ i - m_length ];

				m_length = newLength;

				return *this;
			}

			GenericString< T >& Insert( size_t _index, T _c )
			{
				if( _index >= m_length )
				{
					// TODO: throw exception
				}

				Reserve( m_length );

				for( size_t i = m_length; i > _index; --i )
					m_pBuffer[ i ] = m_pBuffer[ i - 1 ];

				m_pBuffer[ _index ] = _c;

				return *this;
			}

			GenericString< T >& Insert( size_t _index, const GenericString< T >& _str )
			{
				if( _index >= m_length )
				{
					// TODO: throw exception
				}

				Reserve( m_length + _str.m_length );

				for( size_t i = m_length; i > _index; --i )
					m_pBuffer[ i + _str.m_length - 1 ] = m_pBuffer[ i - 1 ];

				for( size_t i = _index; i < _index + _str.m_length - 1; ++i )
					m_pBuffer[ i ] = _str[ i - _index ];

				return *this;
			}

			GenericString< T >& Assign( const GenericString< T >& _str )
			{
				Reserve( _str.m_length );
				m_length = _str.m_length;

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _str[ i ];

				return *this;
			}

			void PushBack( T _c )
			{
				Reserve( m_length );
				m_pBuffer[ m_length++ ] = _c;
			}

			void PopBack( void )
			{
				m_pBuffer[ --m_length ] = 0;
			}

			GenericString< T >& Replace( size_t _index, const GenericString< T >& _str )
			{
				if( _index >= m_length )
				{
					// TODO: Throw exception
				}

				const size_t endIndex = _index + _str.m_length - 1;
				Reserve( endIndex + 1 );

				for( size_t i = _index; i <= endIndex; ++i )
					m_pBuffer[ i ] = _str[ i - _index ];

				return *this;
			}

			GenericString< T >& Replace( const GenericString< T >& _toBeReplaced, const GenericString< T >& _replacement )
			{
				IndexList indices = FindAll( _toBeReplaced );
				if( indices.IsEmpty() )
					return *this;

				if( _replacement.m_length > _toBeReplaced.m_length )
				{
					const size_t sizeDiff = _replacement.m_length - _toBeReplaced.m_length;
					Reserve( m_length + ( sizeDiff * indices.Size() ) );

					for( size_t i = 0; i < indices.Size(); ++i )
					{
						for( size_t j = m_length; j > indices[ i ]; --j )
							m_pBuffer[ j + sizeDiff - 1 ] = m_pBuffer[ j - 1 ];

						for( size_t j = 0; j < _replacement.m_length; ++j )
							m_pBuffer[ indices[ i ] + j ] = _replacement[ j ];

						m_length += sizeDiff;
					}

					return *this;
				}
				else if( _toBeReplaced.m_length > _replacement.m_length )
				{
					const size_t sizeDiff = _toBeReplaced.m_length - _replacement.m_length;

					for( size_t i = 0; i < indices.Size(); ++i )
					{
						for( size_t j = indices[ i ] + _replacement.m_length; j < m_length - 1; ++j )
							m_pBuffer[ j ] = m_pBuffer[ j + 1 ];

						for( size_t j = 0; j < _replacement.m_length; ++j )
							m_pBuffer[ indices[ i ] + j ] = _replacement[ j ];

						m_length -= sizeDiff;
					}

					return *this;
				}

				for( size_t i = 0; i < indices.Size(); ++i )
					Replace( indices[ i ], _replacement );

				return *this;
			}

			GenericString< T >& Replace( T _toBeReplaced, T _replacement )
			{
				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] == _toBeReplaced )
						m_pBuffer[ i ] = _replacement;

				return *this;
			}

			void Reserve( size_t _capacity )
			{
				if( ++_capacity <= m_capacity )
					return;

				m_capacity  = NextPowerOfTwo( _capacity );
				T* pTemp = new T[ m_capacity ];

				Memory::MemorySet( pTemp, ( T )0, m_capacity );

				if( m_pBuffer )
				{
					for( size_t i = 0; i < m_length; ++i )
						pTemp[ i ] = m_pBuffer[ i ];
				}
				
				delete m_pBuffer;
				m_pBuffer = pTemp;

			}

			const T* CString ( void ) const
			{
				return m_pBuffer;
			}

			size_t FindFirst( T _c )            const
			{
				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] == _c )
						return i;

				return m_length;
			}

			size_t FindFirst( const GenericString< T >& _str ) const
			{
				for( size_t i = 0; i < m_length - _str.m_length; ++i )
				{
					bool bFound = true;
					for( size_t j = i; j < i + _str.m_length; ++j )
					{
						if( m_pBuffer[ j ] != _str[ j - i ] )
						{
							bFound = false;
							break;
						}
					}

					if( bFound )
						return i;
				}

				return m_length;
			}

			size_t FindLast( T _c ) const
			{
				for( size_t i = m_length; i > 0; --i )
					if( m_pBuffer[ i - 1 ] == _c )
						return i - 1;

				return m_length;
			}

			size_t FindLast( const GenericString< T >& _str ) const
			{
				for( size_t i = m_length - _str.m_length; i > 0 && i > _str.m_length; i -= _str.m_length )
				{
					bool bFound = true;
					for( size_t j = i - 1; j < i + _str.m_length - 1; ++j )
					{
						if( m_pBuffer[ j ] != _str[ j - i ] )
						{
							bFound = false;
							break;
						}
					}

					if( bFound )
						return i;
				}

				return m_length;
			}

			IndexList FindAll( T _c ) const
			{
				IndexList indices;

				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] == _c )
						indices.PushBack( i );

				return indices;
			}

			IndexList FindAll( const GenericString< T >& _str ) const
			{
				IndexList indices;

				// TODO: implement

				return indices;
			}

			T* Data( void )
			{
				return m_pBuffer;
			}

			int ToInt( void ) const
			{
				if( IsEmpty() )
				{
					// TODO: throw exception
				}

				int sign = 1;
				int offset = 0;

				if( m_pBuffer[ 0 ] == T( '-' ) )
				{
					sign = -1;
					offset = 1;
				}

				for( size_t i = offset; i < m_length; ++i )
				{
					if( m_pBuffer[ i ] < T( '0' ) || m_pBuffer[ i ] > T( '9' ) )
					{
						// TODO throw format exception
					}
				}

				int pos = 1;
				int sum = 0;

				for( size_t i = m_length; i > offset; --i, pos *= 10 )
					sum += ( ( m_pBuffer[ i - 1 ] - T( '0' ) ) * pos );

				return sum * sign;
			}

			float ToFloat( void ) const
			{
				if( IsEmpty() )
				{
					// TODO: Throw exception
				}

				float sign = 1.0f;
				int offset = 0;

				if( m_pBuffer[ 0 ] == T( '-' ) )
				{
					sign = -1.0f;
					offset = 1;
				}

				int decimalIndex = 0;
				for( size_t i = offset; i < m_length && m_pBuffer[ i ] != T( '.' ); ++i )
				{
					if( m_pBuffer[ i ] < T( '0' ) || m_pBuffer[ i ] > T( '9' ) )
					{
						// TODO throw format exception
					}

					++decimalIndex;
				}

				for( size_t i = decimalIndex + 1; i < m_length; ++i )
				{
					if( m_pBuffer[ i ] < T( '0' ) || m_pBuffer[ i ] > T( '9' ) )
					{
						// TODO throw format exception
					}
				}

				float integerPart = 0.0f;

				for( size_t i = decimalIndex, pos = 1; i > offset; --i, pos *= 10 )
					integerPart += static_cast< float >( ( ( m_pBuffer[ i - 1 ] - T( '0' ) ) * pos ) );

				integerPart *= sign;

				if( decimalIndex == m_length )
					return integerPart;

				float fractionalPart   = 0.0f;
				float fractionModifier = 1.0f;
				for( size_t i = m_length, pos = 1; i > ( decimalIndex + 1 ); --i, pos *= 10, fractionModifier *= 0.1f )
					fractionalPart += static_cast< float >( ( ( m_pBuffer[ i - 1 ] - T( '0' ) ) * pos ) );

				return integerPart + ( fractionalPart * fractionModifier );
			}

			size_t Count( T _c ) const
			{
				return FindAll( _c ).Size();
			}

			size_t Count( const GenericString< T >& _str ) const
			{
				return FindAll( _str ).Size();
			}

			StringList Split( T _c = ' ' ) const
			{
				StringList list;
				list.PushBack( GenericString< T >() );

				for( size_t i = 0; i < m_length; ++i )
				{
					if( m_pBuffer[ i ] != _c )
						list.Back().PushBack( m_pBuffer[ i ] );
					else
						list.PushBack( GenericString< T >() );
				}

				return list;
			}

			GenericString< T > AsUpper( void ) const
			{
				GenericString< T > str = *this;
				str.ToUpper();
				return str;
			}

			void ToUpper( void )
			{
				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] >= ( T )'a' && m_pBuffer[ i ] <= ( T )'z' )
						m_pBuffer[ i ] -= ( ( T )'a' - ( T )'A' );
			}

			GenericString< T > AsLower( void ) const
			{
				GenericString< T > str = *this;
				str.ToLower();
				return str;
			}

			void ToLower( void )
			{
				for( size_t i = 0; i < m_length; ++i )
					if( m_pBuffer[ i ] >= ( T )'A' && m_pBuffer[ i ] <= ( T )'Z' )
						m_pBuffer[ i ] += ( ( T )'a' - ( T )'A' );
			}

			void Reverse( void )
			{
				T* pStart = m_pBuffer;
				T* pEnd   = m_pBuffer + m_length - 1;

				while( pStart < pEnd )
					Swap( *pStart++, *pEnd++ );
			}

			GenericString< T > Reversed( void ) const
			{
				GenericString< T > str = *this;
				str.Reverse();
				return str;
			}

			inline T& Back( void )
			{
				// TODO: Throw exception if empty
				return m_pBuffer[ m_length - 1 ];
			}

			inline const T& Back( void ) const
			{
				// TODO: Throw exception if empty
				return m_pBuffer[ m_length - 1 ];
			}

			inline T& Front( void )
			{
				// TODO: Throw exception empty
				return m_pBuffer[ 0 ];
			}

			inline const T& Front( void ) const
			{
				// TODO: Throw exception if empty
				return m_pBuffer[ 0 ];
			}

			inline size_t Size    ( void ) const { return m_length; }
			inline size_t Capacity( void ) const { return m_capacity; }
			inline bool   IsEmpty ( void ) const { return m_length == 0; }

		private:

			size_t m_length;
			size_t m_capacity;
			T*     m_pBuffer;
		};

		using String  = GenericString< char >;
		using WString = GenericString< wchar_t >;
	}
}