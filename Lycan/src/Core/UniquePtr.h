#pragma once

#include "Core.h"
#include "Util.h"

namespace Lycan
{
	namespace Core
	{
		template< class T >
		class UniquePtr
		{
		public:

			UniquePtr()
				: m_pObj( nullptr )
			{}

			UniquePtr( T* _pObj )
				: m_pObj( _pObj )
			{}

			UniquePtr( UniquePtr< T >&& _rSource )
				: m_pObj( _rSource.m_pObj )
			{
				_rSource.m_pObj = nullptr;
			}

			~UniquePtr()
			{
				delete m_pObj;
			}

			UniquePtr( const UniquePtr< T >& ) = delete;
			UniquePtr< T >& operator=( const UniquePtr< T >& ) = delete;

			UniquePtr< T >& operator=( UniquePtr< T >&& _rSource )
			{
				if( this != &_rSource )
				{
					delete m_pObj;
					m_pObj = _rSource.m_pObj;
					_rSource.m_pObj = nullptr;
				}

				return *this;
			}

			T* operator->         ( void )       { return m_pObj; }
			T& operator*          ( void )       { return *m_pObj; }
			explicit operator bool( void ) const { return m_pObj != nullptr; }

			inline T* Get         ( void )       { return m_pObj; }

			T* Release( void )
			{
				T* pTemp = m_pObj;
				m_pObj = nullptr;
				return pTemp;
			}

		private:

			T* m_pObj;

		};

		template< typename T, typename... Args >
		UniquePtr< T > MakeUnique( Args&&... args )
		{
			return UniquePtr< T >( new T( Forward( args... ) ) );
		}
	}
}