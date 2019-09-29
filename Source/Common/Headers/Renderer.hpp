#ifndef __JAM_RENDERER_HPP__
#define __JAM_RENDERER_HPP__

#include <DataTypes.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

namespace Jam
{
	class PolygonCache;

	enum GBUFFER_TYPE
	{
		GBUFFER_TYPE_POSITION = 0,
		GBUFFER_TYPE_ALBEDO,
		GBUFFER_TYPE_TEXCOORD,
		GBUFFER_TOTAL
	};

	typedef struct _tagVERTEX_POSITION
	{
		JAM_FLOAT32 X, Y, Z;
	}VERTEX_POSITION,*PVERTEX_POSITION;

	class Renderer
	{
	public:
		Renderer( );
		~Renderer( );

		JAM_UINT32 Initialise( SDL_Window *p_pWindow );

		JAM_UINT32 RegisterPolygons( const JAM_MEMSIZE p_VertexCount,
			const JAM_MEMSIZE p_IndexCount, const JAM_BYTE *p_pVertices,
			const JAM_UINT16 *p_pIndices, const GLenum p_PrimitiveType,
			const JAM_UINT64 p_VertexAttributes, JAM_UINT32 &p_CacheID );

		JAM_UINT32 GBufferBegin( );
		void GBufferEnd( );

		JAM_UINT32 BeginLightPass( );

		JAM_UINT32 RenderPolygons( const JAM_UINT32 p_CacheID );

		void SetClearColour( const JAM_FLOAT32 p_Red,
			const JAM_FLOAT32 p_Green, const JAM_FLOAT32 p_Blue );

		void Clear( const JAM_BOOL p_ColourBuffer,
			const JAM_BOOL p_DepthBuffer, const JAM_BOOL p_StencilBuffer );
		void SwapBuffers( );

	private:
		SDL_Window		*m_pWindow;
		SDL_GLContext	m_GLContext;
		PolygonCache	*m_pPolygonCache;

		GLuint			m_GBuffer[ GBUFFER_TOTAL ];
		GLuint			m_DepthTexture;
		GLuint			m_Framebuffer;
	};
}

#endif // __JAM_RENDERER_HPP__

