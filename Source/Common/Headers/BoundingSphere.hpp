#ifndef __JAM_BOUNDINGSPHERE_HPP__
#define __JAM_BOUNDINGSPHERE_HPP__

#include <DataTypes.hpp>
#include <Vector4.hpp>
#include <MD5.hpp>

namespace Jam
{
	class Matrix4x4;
	class Renderer;

	class BoundingSphere
	{
	public:
		BoundingSphere( );
		~BoundingSphere( );

		void SetPosition( const Vector4 &p_Position );
		void SetRadius( const JAM_FLOAT32 p_Radius );
		void SetRenderDivisions( const JAM_UINT32 p_Vertical,
			const JAM_UINT32 p_Horizontal );

		JAM_UINT32 GetWorldMatrix( Matrix4x4 &p_Matrix );

		JAM_UINT32 Render( Renderer &p_PolygonCacheManager );

	private:
		JAM_UINT32	m_PolygonCacheID;
		JAM_FLOAT32	m_Radius;
		Vector4		m_Position;
		JAM_UINT32	m_VerticalDivisions;
		JAM_UINT32	m_HorizontalDivisions;
		MD5_DIGEST	m_ShaderMD5;
	};
}

#endif // __JAM_BOUNDINGSPHERE_HPP__

