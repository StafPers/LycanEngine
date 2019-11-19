#include "Math.h"

double LYCAN_API Lycan::Math::Pow( int _base, int _exp )
{
	int val = 1;

	for( int i = 0; i < Abs( _exp ); ++i )
		val *= _base;

	if( Sign( _exp ) == -1 )
		return 1.0 / static_cast< double >( val );

	return static_cast< double >( val );
}

float LYCAN_API Lycan::Math::Round( float _val )
{
	int i = static_cast< int >( _val + 0.5f );
	return static_cast< float >( i );
}

double LYCAN_API Lycan::Math::Round( double _val )
{
	int i = static_cast< int >( _val + 0.5 );
	return static_cast< double >( i );
}

float LYCAN_API Lycan::Math::Floor( float _val )
{
	int i = static_cast< int >( _val );
	return static_cast< float >( i );
}

double LYCAN_API Lycan::Math::Floor( double _val )
{
	int i = static_cast< int >( _val );
	return static_cast< double >( i );
}

float LYCAN_API Lycan::Math::Ceil( float _val )
{
	int i = static_cast< int >( _val + 1.0f );
	return static_cast< float >( i );
}

double LYCAN_API Lycan::Math::Ceil( double _val )
{
	int i = static_cast< int >( _val + 1.0 );
	return static_cast< double >( i );
}
