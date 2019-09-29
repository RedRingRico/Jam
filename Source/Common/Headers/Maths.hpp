#ifndef __JAM_MATHS_HPP__
#define __JAM_MATHS_HPP__

#include <DataTypes.hpp>

namespace Jam
{
	const JAM_FLOAT32 JAM_EPSILON = 1.0e-10;
	const JAM_FLOAT32 JAM_HALF_EPSILON = 1.0e-5;
	const JAM_FLOAT32 JAM_PI = 3.1415926535897932384626433832795f;

	JAM_BOOL IsZero( const JAM_FLOAT32 p_Value );
	JAM_BOOL IsEqual( const JAM_FLOAT32 p_Left, const JAM_FLOAT32 p_Right );

	JAM_FLOAT32 SquareRoot( const JAM_FLOAT32 p_Value );
	JAM_FLOAT32 InvSquareRoot( const JAM_FLOAT32 p_Value );

	JAM_FLOAT32 Absolute( const JAM_FLOAT32 p_Value );

	void SineCosine( const JAM_FLOAT32 p_Angle, JAM_FLOAT32 &p_Sine,
		JAM_FLOAT32 &p_Cosine );
}

#endif // __JAM_MATHS_HPP__

