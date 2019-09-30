#ifndef __JAM_GBUFFER_HPP__
#define __JAM_GBUFFER_HPP__

#include <DataTypes.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

namespace Jam
{
	class GBuffer
	{
	public:
		GBuffer( );
		~GBuffer( );

		ErrorCode Initialise( UInt16 p_Width, UInt16 p_Height );

		void BindForWriting( );
		void BindForReading( );

		enum class GBufferType : UInt32
		{
			Position = 0,
			Diffuse,
			Normal,
			Count
		};

	private:
		GLuint	m_Framebuffer;
		GLuint	*m_pTextures;
		GLuint	m_DepthTexture;
	};
}

#endif // __JAM_GBUFFER_HPP__
