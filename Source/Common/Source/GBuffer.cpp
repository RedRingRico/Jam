#include <GBuffer.hpp>
#include <iostream>

namespace Jam
{
	GBuffer::GBuffer( )	:
		m_Framebuffer( 0 ),
		m_pTextures( NullPtr ),
		m_DepthTexture( 0 )
	{
	}

	GBuffer::~GBuffer( )
	{
		if( m_Framebuffer != 0 )
		{
			glDeleteFramebuffers( 1, &m_Framebuffer );
		}

		if( m_pTextures != NullPtr )
		{
			glDeleteTextures( static_cast< GLsizei >( GBufferType::Count ), m_pTextures );

			delete [ ] m_pTextures;
		}

		if( m_DepthTexture != 0 )
		{
			glDeleteTextures( 1, &m_DepthTexture );
		}
	}

	ErrorCode GBuffer::Initialise( UInt16 p_Width, UInt16 p_Height )
	{
		// Create the framebuffer and associate the textures with it
		glGenFramebuffers( 1, &m_Framebuffer );
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_Framebuffer );

		// Allocate the textures
		m_pTextures = new GLuint[ static_cast< MemSize >( GBufferType::Count ) ];
		glGenTextures( static_cast< GLsizei >( GBufferType::Count ), m_pTextures );
		glGenTextures( 1, &m_DepthTexture );

		for( MemSize Texture = 0; Texture < static_cast< MemSize >( GBufferType::Count );
			++Texture )
		{
			glBindTexture( GL_TEXTURE_2D, m_pTextures[ Texture ] );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F, p_Width, p_Height, 0, GL_RGB, GL_FLOAT,
				NullPtr );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Texture, GL_TEXTURE_2D,
				m_pTextures[ Texture ], 0 );
		}

		glBindTexture( GL_TEXTURE_2D, m_DepthTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, p_Width, p_Height, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, NullPtr );
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture,
			0 );

		GLenum DrawBuffers[ ] =
		{
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2
		};

		glDrawBuffers( sizeof( DrawBuffers ) / sizeof( DrawBuffers[ 0 ] ), DrawBuffers );

		GLenum Error = glCheckFramebufferStatus( GL_FRAMEBUFFER );

		if( Error != GL_FRAMEBUFFER_COMPLETE )
		{
			std::cout << "[Jam::GBuffer::Initialise] <ERROR> Framebuffer creation error: 0x" <<
				std::hex << static_cast< SInt32 >( Error ) << std::dec << std::endl;

			return ErrorCode::FatalError;
		}

		// Restore the default framebuffer
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

		return ErrorCode::Okay;
	}

	void GBuffer::BindForWriting( )
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_Framebuffer );
	}

	void GBuffer::BindForReading( )
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

		for( UInt32 Texture = 0; Texture < static_cast< UInt32 >( GBufferType::Count ); ++Texture )
		{
			glActiveTexture( GL_TEXTURE0 + Texture );
			glBindTexture( GL_TEXTURE_2D, m_pTextures[ Texture ] );
		}
	}
}
