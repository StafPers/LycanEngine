#pragma once

#include "Core.h"
#include "DynamicArray.h"

namespace Lycan
{
	namespace Core
	{
		class LYCAN_API String
		{
		public:

			using IndexList = DynamicArray< size_t >;

			String                 ( void );
			String                 ( const char* _pStr );
			String                 ( char _c, size_t _count );
			String                 ( size_t _capactiy );
			// TODO: Variadic template constructor to format string upon construction 
			String                 ( const String& _rSource );
			String                 ( String&& _rSource );
			~String                ( void );

			String&     operator=  ( const String& _rSource );
			String&     operator=  ( String&& _rSource );
			String      operator+  ( const String& _rhs ) const;
			String&     operator+= ( const String& _rhs );
			const char& operator[] ( size_t _index )      const;
			char&       operator[] ( size_t _index );
			bool        operator== ( const String& _rhs ) const;
			bool        operator!= ( const String& _rhs ) const;


			// TODO: Might need overloads for const char* if they don't implicitly convert
			String&     Append     ( const String& _rOther );
			String&     Insert     ( size_t _index, char _c );
			String&     Insert     ( size_t _index, const String& _str );
			String&     Assign     ( const String& _str );
			void        PushBack   ( char _c );
			void        PopBack    ( void );
			String&     Replace    ( size_t _index, const String& _str );
			String&     Replace    ( const String& _toBeReplaced, const String& _replacement );
			String&     Replace    ( char _toBeReplaced, char _replacement );
			void        Reserve    ( size_t _capacity );

			const char* CString    ( void )               const;
			size_t      FindFirst  ( char _c )            const;
			size_t      FindFirst  ( const String& _str ) const;
			size_t      FindLast   ( char _c )            const;
			size_t      FindLast   ( const String& _str ) const;
			IndexList   FindAll    ( char _c )            const;
			IndexList   FindAll    ( const String& _str ) const;
			char*       Data       ( void );

			int         ToInt      ( void )               const;
			float       ToFloat    ( void )               const;

			size_t      Count      ( char _c )            const;
			size_t      Count      ( const String& _str ) const;

			// split

			// substring

		private:

			size_t m_length;
			size_t m_capactiy;
			char*  m_pBuffer;

		};
	}
}