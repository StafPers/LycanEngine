#pragma once

#include "Algorithm.h"
#include "Core.h"

namespace Lycan
{
	namespace Core
	{
		template< typename T >
		class Queue
		{
		public:

			Queue( void )
				: m_pFront { nullptr }
				, m_pBack  { nullptr }
			{}

			Queue( const Queue< T >& _rOther )
			{
				Copy( _rOther );
			}

			~Queue( void )
			{
				FreeMemory();
			}

			Queue< T >& operator=( const Queue< T >& _rOther )
			{
				if( *this == _rOther )
					return *this;

				FreeMemory();
				Copy( _rOther );
				return *this;
			}

			void Add( const T& _obj )
			{
				if( Empty() )
				{
					m_pFront = m_pBack = new sNode( _obj );
				}
				else
				{
					sNode* pNode = new sNode( _obj );
					m_pBack->pNext = pNode;
					m_pBack = pNode;
				}
			}

			T Dequeue( void )
			{
				if( Empty() )
				{
					// TODO: Throw exception
				}

				sNode* pNext = m_pFront->pNext;
				T&& obj      = Move( m_pFront->obj );

				delete m_pFront;
				m_pFront = pNext;

				return obj;
			}

			T& Front( void ) 
			{
				if( m_pFront == nullptr )
				{
					// TODO: Throw exception
				}

				return m_pFront->obj; 
			}

			const T& Front( void ) const
			{
				if( m_pFront == nullptr )
				{
					// TODO: Throw exception
				}

				return m_pFront->obj;
			}

			T& Back( void )
			{
				if( m_pBack == nullptr )
				{
					// TODO: Throw exception
				}

				return m_pBack->obj;
			}

			const T& Back( void ) const
			{
				if( m_pBack == nullptr )
				{
					// TODO: Throw exception
				}

				return m_pBack->obj;
			}

			bool Empty( void ) const
			{
				return m_pFront == nullptr;
			}

		private:

			struct sNode
			{
				sNode( void ) = default;

				sNode( const T& _rObj, sNode* _pNext = nullptr )
					: obj   { _rObj }
					, pNext { _pNext }
				{}

				T obj;
				sNode* pNext;
			};

			void FreeMemory( void )
			{
				sNode* pCurrent = m_pFront;
				sNode* pNext;

				while( pCurrent != nullptr )
				{
					pNext = pCurrent->pNext;
					delete pCurrent;
					pCurrent = pNext;
				}

				m_pFront = m_pBack = nullptr;
			}

			void Copy( const Queue< T >& _rOther )
			{
				if( _rOther.Empty() )
				{
					m_pFront = nullptr;
					m_pBack = nullptr;
					return;
				}

				sNode* pCurrent = _rOther.m_pFirst;

				while( pCurrent != nullptr )
				{
					Add( pCurrent->obj );
					pCurrent = pCurrent->pNext;
				}
			}

			sNode* m_pFront;
			sNode* m_pBack;
		};
	}
}