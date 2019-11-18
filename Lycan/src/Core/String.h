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
				, m_capactiy { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( 5 );
			}

			GenericString( const T* _pStr )
				: m_length   { Strlen( _pStr ) + 1 }
				, m_capactiy { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _pStr[ i ];
			}

			GenericString( T _c, size_t _count )
				: m_length   { _count }
				, m_capactiy { 0 }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_length );
				Memory::MemorySet( m_pBuffer, _c, _count );
			}

			GenericString( size_t _capactiy )
				: m_length   { 0 }
				, m_capactiy { _capactiy }
				, m_pBuffer  { nullptr }
			{
				Reserve( m_capactiy );
			}

			template< typename... Args >
			GenericString( const T* _str, Args&&... _args )
				: m_length   { 0 }
				, m_capactiy { 0 }
				, m_pBuffer  { nullptr }
			{
				Format( _str, _args... );
			}

			GenericString( const GenericString< T >& _rSource )
			{
				m_length   = _rSource.m_length;
				m_capactiy = _rSource.m_capactiy;
				delete m_pBuffer;
				m_pBuffer = new T[ m_capactiy ];

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];
			}

			GenericString( GenericString< T >&& _rSource )
				: m_length{ 0 }
				, m_capactiy{ 0 }
				, m_pBuffer{ nullptr }
			{
				Swap( *this, _rSource );
			}

			~GenericString( void )
			{
				delete[] m_pBuffer;
			}

			GenericString& operator=( const GenericString< T >& _rSource )
			{
				if( &_rSource == this )
					return *this;

				m_length   = _rSource.m_length;
				m_capactiy = _rSource.m_capactiy;
				delete m_pBuffer;
				m_pBuffer = new T[ m_capactiy ];

				for( size_t i = 0; i < m_length; ++i )
					m_pBuffer[ i ] = _rSource[ i ];

				return *this;
			}

			GenericString& operator=( GenericString< T >&& _rSource )
			{
				m_length   = 0;
				m_capactiy = 0;
				delete m_pBuffer;
				m_pBuffer  = nullptr;
				Swap( *this, _rSource );

				return *this;
			}

			GenericString operator+( const GenericString< T >& _rhs ) const
			{
				GenericString< T > str = *this;
				return str.Append( _rhs );
			}

			GenericString& operator+=( const GenericString< T >& _rhs )
			{
				return *this = *this + _rhs;
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

				Reserve( m_length + 1 );

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
				Reserve( m_length + 1 );
				m_pBuffer[ m_length++ ] = _c;
			}

			void PopBack( void )
			{
				--m_length;
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
				if( ++_capacity <= m_capactiy )
					return;

				m_capactiy  = NextPowerOfTwo( _capacity );
				T* pTemp = new T[ m_capactiy ];

				Memory::MemorySet( pTemp, ( T )0, m_capactiy );

				delete m_pBuffer;
				m_pBuffer = pTemp;

				for( size_t i = 0; i < m_length; ++i )
					pTemp[ i ] = m_pBuffer[ i ];
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
				int sign = 1;
				int offset = 0;

				if( m_pBuffer[ 0 ] == '-' )
				{
					sign = -1;
					offset = 1;
				}

				for( size_t i = offset; i < m_length; ++i )
				{
					if( m_pBuffer[ i ] < '0' || m_pBuffer[ i ] > '9' )
					{
						// TODO throw format exception
					}
				}

				int pos = 1;
				int sum = 0;

				for( size_t i = m_length; i > offset; --i, pos *= 10 )
					sum += m_pBuffer[ i - 1 ] - '0' * pos;

				return sum * sign;
			}

			float ToFloat( void ) const
			{
				// TODO: implement

				return 0.0f;
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

		private:

			template< typename... Args >
			void Format( const char* _str, Args&&... _args )
			{
				m_length = snprintf( nullptr, 0, _str, _args... ) + 1;
				Reserve( m_length );
				snprintf( m_pBuffer, m_length, _str, _args... );
			}

			template< typename... Args >
			void Format( const wchar_t* _str, Args&&... _args )
			{
				m_length =  _snwprintf( nullptr, 0, _str, _args... ) + 1;
				Reserve( m_length );
				_snwprintf( m_pBuffer, m_length, _str, _args... );
			}

			size_t Strlen( const T* _str )
			{
				size_t count = 0;
				for( size_t i = 0; _str[ i ] != 0; ++i, ++count );
				return count;
			}

			size_t m_length;
			size_t m_capactiy;
			T*     m_pBuffer;
		};

		using String  = GenericString< char >;
		using WString = GenericString< wchar_t >;
	}
}