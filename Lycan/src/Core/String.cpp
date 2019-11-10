#include "String.h"

#include "Algorithm.h"
#include "Memory.h"
#include "Util.h"

namespace Lycan
{
	namespace Core
	{
		String::String( void )
			: m_length   { 0 }
			, m_capactiy { 8}
			, m_pBuffer  { new char[ m_capactiy ] }
		{}

		String::String( const char* _pStr )
			: m_length   { sizeof( _pStr ) - 1 }
			, m_capactiy { NextPowerOfTwo( m_length ) }
			, m_pBuffer  { new char[ m_capactiy ] }
		{
			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _pStr[ i ];
		}

		String::String( char _c, size_t _count )
			: m_length   { _count }
			, m_capactiy { NextPowerOfTwo( _count ) }
			, m_pBuffer  { new char[ m_capactiy ] }
		{
			for( size_t i = 0; i < m_length; ++i )
				m_pBuffer[ i ] = _c;
		}

		String::String( size_t _capactiy )
			: m_length   { 0 }
			, m_capactiy { NextPowerOfTwo( _capactiy ) }
			, m_pBuffer  { new char[ m_capactiy ] }
		{}

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
			// TODO: insert return statement here
		}

		String& String::Insert( size_t _index, const String& _str )
		{
			// TODO: insert return statement here
		}

		String& String::Assign( const String& _str )
		{
			// TODO: insert return statement here
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

			size_t sizeDiff = 0;
			if( _replacement.m_length > _toBeReplaced.m_length )
			{
				sizeDiff = _replacement.m_length - _toBeReplaced.m_length;
				Reserve( m_length + ( sizeDiff * indices.Size() ) );

				for( size_t i = 0; i < indices.Size(); ++i )
				{
					// TODO: shift characters to the right with size diff starting at indices[i]
					for( size_t j = 0; j < _replacement.m_length; ++j )
						m_pBuffer[ indices[ i ] + j ] = _replacement[ j ];
				}

				return *this;
			}
			else if( _toBeReplaced.m_length > _replacement.m_length )
			{
				for( size_t i = 0; i < indices.Size(); ++i )
				{
					for( size_t j = 0; j < _replacement.m_length; ++j )
						m_pBuffer[ indices[ i ] + j ] = _replacement[ j ];

					// TODO: need to shift characters to the lef in order to overwrite leftover chars
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
		}

		void String::Reserve( size_t _capacity )
		{
			if( _capacity <= m_capactiy )
				return;

			m_capactiy = NextPowerOfTwo( _capacity );
			char* pTemp = new char[ m_capactiy ];

			for( size_t i = 0; i < m_length; ++i )
				pTemp[ i ] = m_pBuffer[ i ];

			delete m_pBuffer;
			m_pBuffer = pTemp;
		}
	}
}
