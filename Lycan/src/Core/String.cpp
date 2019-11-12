#include "String.h"

#include "Algorithm.h"
#include "Memory.h"
#include "Util.h"

#include <string.h>

namespace Lycan
{
	namespace Core
	{
		String::String( void )
			: m_length   { 0 }
			, m_capactiy { 0 }
			, m_pBuffer  { nullptr }
		{
			Reserve( 5 );
		}

		String::String( const char* _pStr )
			: m_length   { strlen( _pStr ) + 1 }
			, m_capactiy { 0 }
			, m_pBuffer  { nullptr }
		{
			Reserve( m_length );

			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _pStr[ i ];
		}

		String::String( char _c, size_t _count )
			: m_length   { _count }
			, m_capactiy { 0 }
			, m_pBuffer  { nullptr }
		{
			Reserve( m_length );
			MemorySet( m_pBuffer, _c, _count );
		}

		String::String( size_t _capactiy )
			: m_length   { 0 }
			, m_capactiy { _capactiy }
			, m_pBuffer  { nullptr }
		{
			Reserve( m_capactiy );
		}

		String::String( const String& _rSource )
		{
			m_length = _rSource.m_length;
			m_capactiy = _rSource.m_capactiy;
			delete m_pBuffer;
			m_pBuffer = new char[ m_capactiy ];

			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _rSource[ i ];
		}

		String::String( String&& _rSource )
			: m_length   { 0 }
			, m_capactiy { 0 }
			, m_pBuffer  { nullptr }
		{
			Swap( *this, _rSource );
		}

		String::~String( void )
		{
			delete[] m_pBuffer;
		}

		String& String::operator=( const String& _rSource )
		{
			if( &_rSource == this )
				return *this;

			m_length   = _rSource.m_length;
			m_capactiy = _rSource.m_capactiy;
			delete m_pBuffer;
			m_pBuffer = new char[ m_capactiy ];

			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _rSource[ i ];

			return *this;
		}

		String& String::operator=( String&& _rSource )
		{
			m_length   = 0;
			m_capactiy = 0;
			delete m_pBuffer;
			m_pBuffer  = nullptr;
			Swap( *this, _rSource );
			
			return *this;
		}

		String String::operator+( const String& _rhs ) const
		{
			String str = *this;
			return str.Append( _rhs );
		}

		String& String::operator+=( const String& _rhs )
		{
			return *this = *this + _rhs;
		}

		const char& String::operator[]( size_t _index ) const
		{
			if( _index >= m_length )
			{
				// TODO: Throw exception
			}

			return m_pBuffer[ _index ];
		}

		char& String::operator[]( size_t _index )
		{
			if( _index >= m_length )
			{
				// TODO: Throw exception
			}

			return m_pBuffer[ _index ];
		}

		bool String::operator==( const String& _rhs ) const
		{
			if( m_length != _rhs.m_length )
				return false;

			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] != _rhs[ i ] )
					return false;

			return true;
		}

		bool String::operator!=( const String& _rhs ) const
		{
			return !( *this == _rhs );
		}

		String& String::Append( const String& _rOther )
		{
			const size_t newLength = m_length + _rOther.m_length;
			Reserve( newLength );

			for( size_t i = m_length; i < newLength; ++i )
				m_pBuffer[ i ] = _rOther[ i - m_length ];

			m_length = newLength;

			return *this;
		}

		String& String::Insert( size_t _index, char _c )
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

		String& String::Insert( size_t _index, const String& _str )
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

		String& String::Assign( const String& _str )
		{
			Reserve( _str.m_length );
			m_length = _str.m_length;

			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _str[ i ];

			return *this;
		}

		void String::PushBack( char _c )
		{
			Reserve( m_length + 1 );
			m_pBuffer[ m_length++ ] = _c;
		}

		void String::PopBack( void )
		{
			--m_length;
		}

		String& String::Replace( size_t _index, const String& _str )
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

		String& String::Replace( const String& _toBeReplaced, const String& _replacement )
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

		String& String::Replace( char _toBeReplaced, char _replacement )
		{
			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] == _toBeReplaced )
					m_pBuffer[ i ] = _replacement;

			return *this;
		}

		void String::Reserve( size_t _capacity )
		{
			if( ++_capacity <= m_capactiy )
				return;

			m_capactiy  = NextPowerOfTwo( _capacity );
			char* pTemp = new char[ m_capactiy ];

			MemorySet( pTemp, 0, m_capactiy );

			delete m_pBuffer;
			m_pBuffer = pTemp;

			for( size_t i = 0; i < m_length; ++i )
				pTemp[ i ] = m_pBuffer[ i ];
		}

		const char* String::CString( void ) const
		{
			return m_pBuffer;
		}

		size_t String::FindFirst( char _c ) const
		{
			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] == _c )
					return i;

			return m_length;
		}

		size_t String::FindFirst( const String& _str ) const
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

		size_t String::FindLast( char _c ) const
		{
			for( size_t i = m_length; i > 0; --i )
				if( m_pBuffer[ i - 1 ] == _c )
					return i - 1;

			return m_length;
		}

		size_t String::FindLast( const String & _str ) const
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

		String::IndexList String::FindAll( char _c ) const
		{
			IndexList indices;

			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] == _c )
					indices.PushBack( i );

			return indices;
		}

		String::IndexList String::FindAll( const String& _str ) const
		{
			IndexList indices;

			// TODO: implement

			return indices;
		}

		char* String::Data( void )
		{
			return m_pBuffer;
		}

		int String::ToInt( void ) const
		{
			int sign   = 1;
			int offset = 0;

			if( m_pBuffer[ 0 ] == '-' )
			{
				sign   = -1;
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

		float String::ToFloat( void ) const
		{
			// TODO: implement

			return 0.0f;
		}

		size_t String::Count( char _c ) const
		{
			return FindAll( _c ).Size();
		}

		size_t String::Count( const String& _str ) const
		{
			return FindAll( _str ).Size();
		}

		String::StringList String::Split( char _c ) const
		{
			StringList list;
			list.PushBack( String() );

			for( size_t i = 0; i < m_length; ++i )
			{
				if( m_pBuffer[ i ] != _c )
					list.Back().PushBack( m_pBuffer[ i ] );
				else
					list.PushBack( String() );
			}

			return list;
		}

		String String::AsUpper( void ) const
		{
			String str = *this;
			str.ToUpper();
			return str;
		}

		void String::ToUpper( void )
		{
			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] >= 'a' && m_pBuffer[ i ] <= 'z' )
					m_pBuffer[ i ] -= ( 'a' - 'A' );
		}

		String String::AsLower( void ) const
		{
			String str = *this;
			str.ToLower();
			return str;
		}

		void String::ToLower( void )
		{
			for( size_t i = 0; i < m_length; ++i )
				if( m_pBuffer[ i ] >= 'A' && m_pBuffer[ i ] <= 'Z' )
					m_pBuffer[ i ] += ( 'a' - 'A' );
		}

		void String::Reverse( void )
		{
			char* pStart = m_pBuffer;
			char* pEnd   = m_pBuffer + m_length - 1;

			while( pStart < pEnd )
				Swap( *pStart++, *pEnd++ );
		}

		String String::Reversed( void ) const
		{
			String str = *this;
			str.Reverse();
			return str;
		}
	}
}
