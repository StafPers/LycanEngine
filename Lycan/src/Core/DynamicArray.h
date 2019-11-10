#pragma once

#include "Algorithm.h"
#include "Core.h"

#include <new>

namespace Lycan
{
	namespace Core
	{
		template< class T >
		class LYCAN_API DynamicArray
		{
		public:

			DynamicArray( void )
				: DynamicArray{ 8 }
			{}

			DynamicArray( size_t _capacity )
				: m_numElements { 0 }
				, m_capacity    { NextPowerOfTwo( _capacity ) }
				, m_pBuffer     { new char[ m_capacity * sizeof( T ) ] }
			{
			}

			DynamicArray( size_t _numElements, T _value )
				: m_numElements { _numElements }
				, m_capacity    { NextPowerOfTwo( _numElements ) }
				, m_pBuffer     { new char[ m_capacity * sizeof( T ) ] }
			{
				for( size_t i = 0; i < m_numElements; ++i )
					new( reinterpret_cast< T* >( m_pBuffer ) + i ) T( _value );
			}

			DynamicArray( const DynamicArray& _rSource )
				: m_numElements { _rSource.m_numElements }
				, m_capacity    { _rSource.m_numElements }
				, m_pBuffer     { new char[ _rSource.m_numElements * sizeof( T ) ] }
			{
				for( size_t i = 0; i < m_numElements; ++i )
					new( reinterpret_cast< T* >( m_pBuffer ) + i ) T( _rSource[ i ] );
			}

			DynamicArray( DynamicArray&& _rSource )
				: m_numElements { _rSource.m_numElements }
				, m_capacity    { _rSource.m_capacity }
				, m_pBuffer     { _rSource.m_pBuffer }
			{
				_rSource.m_numElements = 0;
				_rSource.m_capacity = 0;
				_rSource.m_pBuffer = nullptr;
			}

			~DynamicArray()
			{
				for( size_t i = 0; i < m_numElements; ++i )
					reinterpret_cast< T* >( m_pBuffer )[ i ].~T();

				delete[] m_pBuffer;
			}

			DynamicArray& operator=( const DynamicArray& _rSource )
			{
				if( &_rSource != this )
				{
					delete[] m_pBuffer;

					m_numElements = _rSource.m_numElements;
					m_capacity = _rSource.m_capacity;
					m_pBuffer = new char[ m_numElements * sizeof( T ) ];

					for( size_t i = 0; i < m_numElements; ++i )
						new( reinterpret_cast< T* >( m_pBuffer ) + i ) T( _rSource[ i ] );
				}

				return *this;
			}

			DynamicArray& operator=( DynamicArray&& _rSource )
			{
				if( &_rSource != this )
				{
					delte[] m_pBuffer;

					m_numElements = _rSource.m_numElements;
					m_capacity = _rSource.m_capacity;
					m_pBuffer = _rSource.m_pBuffer;

					_rSource.m_numElements = 0;
					_rSource.m_capacity = 0;
					_rSource.m_pBuffer = nullptr;
				}

				return *this;
			}

			const T& operator[]( size_t _index ) const
			{
				// TODO: Throw IndexOutOfRange if in_uIndex >= m_uNumElements
				return reinterpret_cast< T* >( m_pBuffer )[ _index ];
			}

			T& operator[]( size_t _index )
			{
				return const_cast< T& >( static_cast< const DynamicArray< T >& >( *this )[ _index ] );
			}

			void Reserve( size_t _size )
			{
				if( m_capacity < _size )
				{
					m_capacity = NextPowerOfTwo( _size );

					char* pTemp = new char[ m_capacity * sizeof( T ) ];

					for( size_t i = 0; i < m_numElements; ++i )
					{
						const T* pOldObject = reinterpret_cast< const T* >( m_pBuffer ) + i;
						new( reinterpret_cast< T* >( pTemp ) + i ) T( *pOldObject );
						pOldObject->~T();
					}

					delete[] m_pBuffer;
					m_pBuffer = pTemp;
				}
			}

			void Resize( size_t _size, const T& _rValue = T() )
			{
				Reserve( _size );

				if( _size < m_numElements )
				{
					for( size_t i = _size; i < m_numElements; ++i )
						reinterpret_cast< T* >( m_pBuffer )[ i ].~T();
				}
				else
				{
					for( size_t i = m_numElements; i < _size; ++i )
						new( reinterpret_cast< T* >( m_pBuffer ) + i ) T( _rValue );
				}

				m_numElements = _size;
			}

			void PushBack( const T& _rValue )
			{
				Reserve( m_numElements + 1 );

				new( reinterpret_cast< T* >( m_pBuffer ) + m_numElements++ ) T( _rValue );
			}

			void PushBack( const DynamicArray< T >& _rOther )
			{
				Reserve( m_numElements + _rOther.m_numElements );

				for( size_t i = m_numElements; i < ( m_numElements + _rOther.m_numElements ); ++i )
					new( reinterpret_cast< T* >( m_pBuffer ) + i )
					T( reinterpret_cast< T* >( _rOther.m_pBuffer )[ i - m_numElements ] );

				m_numElements += _rOther.m_numElements;
			}

			void PopBack( void )
			{
				// TODO: throw exception if trying to pop empty array
				if( IsEmpty() )
					return;

				reinterpret_cast< T* >( m_pBuffer )[ m_numElements-- - 1 ].~T();
			}

			void PushFront( const T& _rValue )
			{
				Reserve( m_numElements + 1 );

				new( reinterpret_cast< T* >( m_pBuffer ) + m_numElements ) T();

				for( size_t i = m_numElements++; i > 0; --i )
					reinterpret_cast< T* >( m_pBuffer )[ i ] = reinterpret_cast< T* >( m_pBuffer )[ i - 1 ];

				reinterpret_cast< T* >( m_pBuffer )[ 0 ] = _rValue;
			}

			void PushFront( const DynamicArray< T >& _rOther )
			{
				Reserve( m_numElements + _rOther.m_numElements );

				for( size_t i = m_numElements; i > 0; --i )
				{
					new( reinterpret_cast< T* >( m_pBuffer ) + i + _rOther.m_numElements - 1 )
						T( reinterpret_cast< T* >( m_pBuffer )[ i - 1 ] );

					reinterpret_cast< T* >( m_pBuffer )[ i - 1 ].~T();
				}

				for( size_t i = 0; i < _rOther.m_numElements; ++i )
					new( reinterpret_cast< T* >( m_pBuffer ) + i )
					T( reinterpret_cast< T* >( _rOther.m_pBuffer )[ i ] );
			}

			void PopFront( void )
			{
				// TODO: Throw exception if tryng to pop empty array
				if( IsEmpty() )
					return;

				for( size_t i = 0; i < m_numElements - 1; ++i )
					reinterpret_cast< T* >( m_pBuffer )[ i ] = reinterpret_cast< T* >( m_pBuffer )[ i + 1 ];

				reinterpret_cast< T* >( m_pBuffer )[ --m_numElements ].~T();
			}

			template< typename... Args >
			void EmplaceBack( Args&&... args )
			{
				Reserve( m_numElements + 1 );

				new( reinterpret_cast< T* >( m_pBuffer ) + m_numElements++ ) T( args... );
			}

			void Insert( const T& _rValue, size_t _index )
			{
				// TODO: Throw exception if index out of bound
				if( _index >= m_numElements )
					return;

				Reserve( m_numElements + 1 );
				new( reinterpret_cast< T* >( m_pBuffer ) + m_numElements ) T();

				for( size_t i = m_numElements++; i > _index; --i )
				{
					reinterpret_cast< T* >( m_pBuffer )[ i ] = reinterpret_cast< T* >( m_pBuffer )[ i - 1 ];
				}

				reinterpret_cast< T* >( m_pBuffer )[ _index ] = _rValue;
			}

			void Insert( const DynamicArray< T >& _rOther, size_t _index )
			{
				// TODO: Throw exception if index out of bounds
				if( _index >= m_numElements )
					return;

				Reserve( m_numElements + _rOther.m_numElements );

				for( size_t i = m_numElements; i > _index; --i )
				{
					new( reinterpret_cast< T* >( m_pBuffer ) + i + _rOther.m_numElements - 1 )
						T( reinterpret_cast< T* >( m_pBuffer )[ i - 1 ] );

					reinterpret_cast< T* >( m_pBuffer )[ i - 1 ].~T();
				}

				for( size_t i = 0; i < _rOther.m_numElements; ++i )
					new( reinterpret_cast< T* >( m_pBuffer ) + i + _index )
					T( reinterpret_cast< T* >( _rOther.m_pBuffer )[ i ] );
			}

			void RemoveAt( size_t _index )
			{
				// TODO: Throw exception if index out of bounds or empty
				if( _index >= m_numElements || IsEmpty() )
					return;

				for( size_t i = _index + 1; i < m_numElements; ++i )
					reinterpret_cast< T* >( m_pBuffer )[ i - 1 ] = reinterpret_cast< T* >( m_pBuffer )[ i ];

				reinterpret_cast< T* >( m_pBuffer )[ --m_numElements ].~T();
			}

			void RemoveFirstOf( const T& _rValue )
			{
				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( reinterpret_cast< T* >( m_pBuffer )[ i ] == _rValue )
					{
						RemoveAt( i );
						return;
					}
				}
			}

			void RemoveAllOf( const T& _rValue )
			{
				size_t uNumRemovedObjects = 0;
				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( reinterpret_cast< T* >( m_pBuffer )[ i - uNumRemovedObjects ] == _rValue )
						RemoveAt( i - uNumRemovedObjects++ );
				}
			}

			void RemoveIf( bool( *Predicate )( const T& ) )
			{
				size_t uNumRemovedObjects = 0;
				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( Predicate( reinterpret_cast< T* >( m_pBuffer )[ i - uNumRemovedObjects ] ) )
						RemoveAt( i - uNumRemovedObjects++ );
				}
			}

			size_t FindFirstOf( const T& _rValue ) const
			{
				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( reinterpret_cast< T* >( m_pBuffer )[ i ] == _rValue )
						return i;
				}

				return m_numElements;
			}

			DynamicArray< size_t > FindAllOf( const T& _rValue ) const
			{
				DynamicArray< size_t > indices;

				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( reinterpret_cast< T* >( m_pBuffer )[ i ] == _rValue )
						indices.PushBack( i );
				}

				return indices;
			}

			size_t FindFirstIf( bool( *Predicate )( const T& ) ) const
			{
				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( Predicate( reinterpret_cast< T* >( m_pBuffer )[ i ] ) )
						return i;
				}

				return m_numElements;
			}

			DynamicArray< size_t > FindAllIf( bool( *Predicate )( const T& ) ) const
			{
				DynamicArray< size_t > indices;

				for( size_t i = 0; i < m_numElements; ++i )
				{
					if( Predicate( reinterpret_cast< T* >( m_pBuffer )[ i ] ) )
						indices.PushBack( i );
				}

				return indices;
			}

			bool Contains( const T& _rValue ) const
			{
				for( size_t i = 0; i < m_numElements; ++i )
					if( reinterpret_cast< T* >( m_pBuffer )[ i ] == _rValue )
						return true;

				return false;
			}

			void Sort( bool( *Predicate )( const T&, const T& ) = []( const T& a, const T& b ) { return b < a; } )
			{
				// TODO: Implement some actually efficient sorting algorithm like Quicksort
				while( true )
				{
					bool bSwapped = false;

					for( size_t i = 0; i < m_numElements - 1; ++i )
					{
						if( Predicate( reinterpret_cast< T* >( m_pBuffer )[ i ], reinterpret_cast< T* >( m_pBuffer )[ i + 1 ] ) )
						{
							bSwapped = true;
							Swap( reinterpret_cast< T* >( m_pBuffer )[ i ], reinterpret_cast< T* >( m_pBuffer )[ i + 1 ] );
						}
					}

					if( bSwapped == false )
						break;
				}
			}

			DynamicArray< T > Sorted( bool( *Predicate )( const T&, const T& ) = []( const T& a, const T& b ) { return b < a; } )
			{
				DynamicArray< T > sortedArray = *this;
				sortedArray.Sort( Predicate );

				return sortedArray;
			}

			void Clear( void )
			{
				for( size_t i = 0; i < m_numElements; ++i )
					reinterpret_cast< T* >( m_pBuffer )[ i ].~T();

				m_numElements = 0;
			}

			void Reverse( void )
			{
				T* pLeft = reinterpret_cast< T* >( m_pBuffer );
				T* pRight = reinterpret_cast< T* >( m_pBuffer ) + m_numElements - 1;

				for( ; pLeft < pRight; ++pLeft, --pRight )
					Swap( *pLeft, *pRight );
			}

			DynamicArray< T > Reversed( void ) const
			{
				DynamicArray< T > reversedArr = *this;
				reversedArr.Reverse();

				return reversedArr;
			}

			size_t CountInstancesOf( const T& _rValue )
			{
				size_t count = 0;
				for( size_t i = 0; i < m_numElements; ++i )
					if( reinterpret_cast< T* >( m_pBuffer )[ i ] == _rValue )
						++count;

				return count;
			}

			inline T& Back( void )
			{
				// TODO: Throw exception if empty
				return reinterpret_cast< T* >( m_pBuffer )[ m_numElements - 1 ];
			}

			inline const T& Back( void ) const
			{
				// TODO: Throw exception if empty
				return reinterpret_cast< T* >( m_pBuffer )[ m_numElements - 1 ];
			}

			inline T& Front( void )
			{
				// TODO: Throw exception empty
				return reinterpret_cast< T* >( m_pBuffer )[ 0 ];
			}

			inline const T& Front( void ) const
			{
				// TODO: Throw exception if empty
				return reinterpret_cast< T* >( m_pBuffer )[ 0 ];
			}

			inline       T*     Data    ( void )       { return reinterpret_cast< T* >( m_pBuffer ); }
			inline const T*     Data    ( void ) const { return reinterpret_cast< T* >( m_pBuffer ); }
			inline       size_t Size    ( void ) const { return m_numElements; }
			inline       size_t Capacity( void ) const { return m_capacity; }
			inline       bool   IsEmpty ( void ) const { return m_numElements == 0; }

		private:

			size_t  m_numElements;
			size_t  m_capacity;
			char*   m_pBuffer;
		};
	}
}