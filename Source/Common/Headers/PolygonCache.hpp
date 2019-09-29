#ifndef __JAM_POLYGONCACHE_HPP__
#define __JAM_POLYGONCACHE_HPP__

#include <DataTypes.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

namespace Jam
{
	typedef struct _POLYGONCACHE
	{
		JAM_UINT32	ID;
		JAM_MEMSIZE	Stride;
		JAM_MEMSIZE	VertexCount;
		JAM_MEMSIZE	IndexCount;
		JAM_MEMSIZE	PolygonCount;
		GLuint		VertexBufferID;
		GLuint		IndexBufferID;
		GLuint		VertexArrayID;
		GLenum		PrimitiveType;
	}POLYGONCACHE,*PPOLYGONCACHE;

	class PolygonCache
	{
	public:
		PolygonCache( );
		~PolygonCache( );

		JAM_UINT32 AddPolygons( const JAM_MEMSIZE p_VertexCount,
			const JAM_MEMSIZE p_IndexCount, const JAM_BYTE *p_pVertices,
			const JAM_UINT16 *p_pIndices, const GLenum p_PrimitiveType,
			const JAM_UINT64 p_VertexAttributes, JAM_UINT32 &p_CacheID );
		
		JAM_UINT32 Render( const JAM_UINT32 p_CacheID );

		JAM_UINT32 DeletePolygons( const JAM_UINT32 p_CacheID );

		void Purge( );

	private:
		std::vector< POLYGONCACHE >	m_Cache;

		JAM_UINT32 m_CacheID;
	};
}

#endif // __JAM_POLYGONCACHE_HPP__

