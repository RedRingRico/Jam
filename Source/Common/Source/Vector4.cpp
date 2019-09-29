#include <Vector4.hpp>
#include <Maths.hpp>
#include <iostream>
#include <cmath>

namespace Jam
{
	Vector4::Vector4( ) :
		m_X( 0.0f ),
		m_Y( 0.0f ),
		m_Z( 0.0f ),
		m_W( 0.0f )
	{
	}

	Vector4::Vector4( const JAM_FLOAT32 p_X, const JAM_FLOAT32 p_Y,
		const JAM_FLOAT32 p_Z, const JAM_FLOAT32 p_W ) :
		m_X( p_X ),
		m_Y( p_Y ),
		m_Z( p_Z ),
		m_W( p_W )
	{
	}

	Vector4::~Vector4( )
	{
	}

	void Vector4::Set( const JAM_FLOAT32 p_X, const JAM_FLOAT32 p_Y,
		const JAM_FLOAT32 p_Z, const JAM_FLOAT32 p_W )
	{
		m_X = p_X;
		m_Y = p_Y;
		m_Z = p_Z;
		m_W = p_W;
	}

	void Vector4::SetX( const JAM_FLOAT32 p_X )
	{
		m_X = p_X;
	}

	void Vector4::SetY( const JAM_FLOAT32 p_Y )
	{
		m_Y = p_Y;
	}

	void Vector4::SetZ( const JAM_FLOAT32 p_Z )
	{
		m_Z = p_Z;
	}

	void Vector4::SetW( const JAM_FLOAT32 p_W )
	{
		m_W = p_W;
	}

	JAM_FLOAT32 Vector4::GetX( ) const
	{
		return m_X;
	}

	JAM_FLOAT32 Vector4::GetY( ) const
	{
		return m_Y;
	}

	JAM_FLOAT32 Vector4::GetZ( ) const
	{
		return m_Z;
	}

	JAM_FLOAT32 Vector4::GetW( ) const
	{
		return m_W;
	}

	JAM_FLOAT32 Vector4::GetMagnitude( ) const
	{
		return ( sqrtf( ( m_X * m_X ) + ( m_Y * m_Y ) + ( m_Z * m_Z ) +
			( m_W * m_W )  ) );
	}

	JAM_FLOAT32 Vector4::GetMagnitudeSq( ) const
	{
		return ( ( m_X * m_X ) + ( m_Y * m_Y ) + ( m_Z * m_Z ) +
			( m_W * m_W ) );
	}

	void Vector4::Normalise( )
	{
		JAM_FLOAT32 Squared = this->GetMagnitudeSq( );

		if( Jam::IsZero( Squared ) )
		{
			this->Zero( );
		}
		else
		{
			JAM_FLOAT32 Factor = Jam::InvSquareRoot( Squared );

			m_X *= Factor;
			m_Y *= Factor;
			m_Z *= Factor;
			m_W *= Factor;
		}
	}

	void Vector4::Zero( )
	{
		m_X = m_Y = m_Z = m_W = 0.0f;
	}

	void Vector4::Clean( )
	{
		if( Jam::IsZero( m_X ) )
		{
			m_X = 0.0f;
		}

		if( Jam::IsZero( m_Y ) )
		{
			m_Y = 0.0f;
		}

		if( Jam::IsZero( m_Z ) )
		{
			m_Z = 0.0f;
		}

		if( Jam::IsZero( m_W ) )
		{
			m_W = 0.0f;
		}
	}

	Vector4 Vector4::CrossProduct( const Vector4 &p_Right ) const
	{
		Vector4 Cross;

		// The W component is assumed to be set correctly by the user
		Cross.m_X = ( m_Y * p_Right.m_Z ) - ( m_Z * p_Right.m_Y );
		Cross.m_Y = ( m_Z * p_Right.m_X ) - ( m_X * p_Right.m_Z );
		Cross.m_Z = ( m_X * p_Right.m_Y ) - ( m_Y * p_Right.m_X );

		return Cross;
	}

	JAM_FLOAT32 Vector4::DotProduct( const Vector4 &p_Right ) const
	{
		return ( ( m_X * p_Right.m_X ) + ( m_Y * p_Right.m_Y ) +
			( m_Z * p_Right.m_Z ) + ( m_W * p_Right.m_W ) );
	}

	JAM_BOOL Vector4::operator==( const Vector4 &p_Right ) const
	{
		if( Jam::IsEqual( m_X, p_Right.m_X ) &&
			Jam::IsEqual( m_Y, p_Right.m_Y ) &&
			Jam::IsEqual( m_Z, p_Right.m_Z ) &&
			Jam::IsEqual( m_W, p_Right.m_W ) )
		{
			return JAM_TRUE;
		}

		return JAM_FALSE;
	}

	JAM_BOOL Vector4::operator!=( const Vector4 &p_Right ) const
	{
		if( Jam::IsEqual( m_X, p_Right.m_X ) &&
			Jam::IsEqual( m_Y, p_Right.m_Y ) &&
			Jam::IsEqual( m_Z, p_Right.m_Z ) &&
			Jam::IsEqual( m_W, p_Right.m_W ) )
		{
			return JAM_FALSE;
		}

		return JAM_TRUE;
	}

	Vector4 &Vector4::operator-( )
	{
		m_X = -m_X;
		m_Y = -m_Y;
		m_Z = -m_Z;
		m_W = -m_W;

		return *this;
	}

	Vector4 Vector4::operator+( const Vector4 &p_Right ) const
	{
		Vector4 Added;

		Added.m_X = m_X + p_Right.m_X;
		Added.m_Y = m_Y + p_Right.m_Y;
		Added.m_Z = m_Z + p_Right.m_Z;
		Added.m_W = m_W + p_Right.m_W;

		return Added;
	}

	Vector4 Vector4::operator-( const Vector4 &p_Right ) const
	{
		Vector4 Subtract;

		Subtract.m_X = m_X - p_Right.m_X;
		Subtract.m_Y = m_Y - p_Right.m_Y;
		Subtract.m_Z = m_Z - p_Right.m_Z;
		Subtract.m_W = m_W - p_Right.m_W;

		return Subtract;
	}

	Vector4 Vector4::operator*( const Vector4 &p_Right ) const
	{
		Vector4 Multiply;

		Multiply.m_X = m_X * p_Right.m_X;
		Multiply.m_Y = m_Y * p_Right.m_Y;
		Multiply.m_Z = m_Z * p_Right.m_Z;
		Multiply.m_W = m_W * p_Right.m_W;

		return Multiply;
	}

	Vector4 Vector4::operator*( const JAM_FLOAT32 p_Scalar ) const
	{
		Vector4 Multiply;

		Multiply.m_X = m_X * p_Scalar;
		Multiply.m_Y = m_Y * p_Scalar;
		Multiply.m_Z = m_Z * p_Scalar;
		Multiply.m_W = m_W * p_Scalar;

		return Multiply;
	}

	Vector4 &Vector4::operator+=( const Vector4 &p_Right )
	{
		m_X *= p_Right.m_X;
		m_Y *= p_Right.m_Y;
		m_Z *= p_Right.m_Z;
		m_W *= p_Right.m_W;

		return *this;
	}

	Vector4 &Vector4::operator-=( const Vector4 &p_Right )
	{
		m_X -= p_Right.m_X;
		m_Y -= p_Right.m_Y;
		m_Z -= p_Right.m_Z;
		m_W -= p_Right.m_W;

		return *this;
	}

	Vector4 &Vector4::operator*=( const Vector4 &p_Right )
	{
		m_X *= p_Right.m_X;
		m_Y *= p_Right.m_Y;
		m_Z *= p_Right.m_Z;
		m_W *= p_Right.m_W;

		return *this;
	}

	Vector4 &Vector4::operator*=( const JAM_FLOAT32 p_Scalar )
	{
		m_X *= p_Scalar;
		m_Y *= p_Scalar;
		m_Z *= p_Scalar;
		m_W *= p_Scalar;

		return *this;
	}

	void Vector4::Print( const std::string &p_Name ) const
	{
		std::cout << p_Name << std::endl;

		std::cout << "< " << m_X << ", " << m_Y << ", " << m_Z << ", " <<
			m_W << " >" << std::endl;
	}
}

