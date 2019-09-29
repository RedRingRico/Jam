#include <Maths.hpp>
#include <cmath>

namespace Jam
{
	JAM_BOOL IsZero( const JAM_FLOAT32 p_Value )
	{
		return ( fabs( p_Value ) < JAM_EPSILON );
	}

	JAM_BOOL IsEqual( JAM_FLOAT32 p_Left, JAM_FLOAT32 p_Right )
	{
		return ( IsZero( p_Left - p_Right ) );
	}

	JAM_FLOAT32 SquareRoot( const JAM_FLOAT32 p_Value )
	{
		return sqrtf( p_Value );
	}

	JAM_FLOAT32 InvSquareRoot( const JAM_FLOAT32 p_Value )
	{
		return ( 1.0f / Jam::SquareRoot( p_Value ) );
	}

	JAM_FLOAT32 Absolute( const JAM_FLOAT32 p_Value )
	{
		return fabs( p_Value );
	}

	void SineCosine( const JAM_FLOAT32 p_Angle, JAM_FLOAT32 &p_Sine,
		JAM_FLOAT32 &p_Cosine )
	{
		p_Sine = sinf( p_Angle );
		p_Cosine = cosf( p_Angle );
	}
}

