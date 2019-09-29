#ifndef __JAM_VECTOR4_HPP__
#define __JAM_VECTOR4_HPP__

#include <DataTypes.hpp>
#include <string>

namespace Jam
{
	class Vector4
	{
	public:
		Vector4( );
		Vector4( const JAM_FLOAT32 p_X, const JAM_FLOAT32 p_Y,
			const JAM_FLOAT32 p_Z, const JAM_FLOAT32 p_W );
		~Vector4( );

		void Set( const JAM_FLOAT32 p_X, const JAM_FLOAT32 p_Y,
			const JAM_FLOAT32 p_Z, const JAM_FLOAT32 p_W );
		void SetX( const JAM_FLOAT32 p_X );
		void SetY( const JAM_FLOAT32 p_Y );
		void SetZ( const JAM_FLOAT32 p_Z );
		void SetW( const JAM_FLOAT32 p_W );

		JAM_FLOAT32 GetX( ) const;
		JAM_FLOAT32 GetY( ) const;
		JAM_FLOAT32 GetZ( ) const;
		JAM_FLOAT32 GetW( ) const;

		JAM_FLOAT32 GetMagnitude( ) const;
		JAM_FLOAT32 GetMagnitudeSq( ) const;

		JAM_FLOAT32 Distance( const Vector4 &p_Right ) const;
		JAM_FLOAT32 DistanceSq( const Vector4 &p_Right ) const;

		void Normalise( );

		void Zero( );
		void Clean( );

		// While the cross product is only valid for 3-element vectors, this
		// will only operate on the first 3 components
		Vector4 CrossProduct( const Vector4 &p_Right ) const;
		JAM_FLOAT32 DotProduct( const Vector4 &p_Right ) const;

		JAM_BOOL operator==( const Vector4 &p_Right ) const;
		JAM_BOOL operator!=( const Vector4 &p_Right ) const;

		Vector4 &operator-( );

		Vector4 operator+( const Vector4 &p_Right ) const;
		Vector4 operator-( const Vector4 &p_Right ) const;
		Vector4 operator*( const Vector4 &p_Right ) const;
		Vector4 operator*( const JAM_FLOAT32 p_Scalar ) const;

		Vector4 &operator+=( const Vector4 &p_Right );
		Vector4 &operator-=( const Vector4 &p_Right );
		Vector4 &operator*=( const Vector4 &p_Right );
		Vector4 &operator*=( const JAM_FLOAT32 p_Scalar );

		void Print( const std::string &p_Name ) const;
		
	private:
		JAM_FLOAT32 m_X, m_Y, m_Z, m_W;
	};

}

#endif // __JAM_VECTOR4_HPP__

