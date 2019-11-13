#pragma once

namespace Lycan
{
	namespace Memory
	{
		template< typename T >
		class SharedPtr
		{
		public:

			SharedPtr( void );
			~SharedPtr( void );

			T* operator->         ( void ) { return m_pObj; }
			T& operator*          ( void ) { return *m_pObj; }
			explicit operator bool( void ) const { return m_pObj != nullptr; }

			inline T* Get         ( void ) { return m_pObj; }

			inline size_t UseCount( void ) const { return m_useCount }

		private:

			T*     m_pObj;
			size_t m_useCount;

		};
	}
}
