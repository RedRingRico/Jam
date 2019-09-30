#include <Renderer.hpp>
#include <PolygonCache.hpp>
#include <Memory.hpp>
#include <iostream>
#include <BoundingSphere.hpp>

namespace Jam
{
	BoundingSphere g_Sphere;

	Renderer::Renderer( ) :
		m_pWindow( JAM_NULL ),
		m_GLContext( JAM_NULL ),
		m_pPolygonCache( JAM_NULL )
	{
	}

	Renderer::~Renderer( )
	{
		SDL_GL_DeleteContext( m_GLContext );
		SafeDelete< PolygonCache >( m_pPolygonCache );
		glDeleteFramebuffers( sizeof( m_GBuffer ) / sizeof( m_GBuffer[ 0 ] ),
			m_GBuffer );
		glDeleteFramebuffers( 1, &m_DepthTexture );
	}

	JAM_UINT32 Renderer::Initialise( SDL_Window *p_pWindow )
	{
		GLenum Error = GL_NO_ERROR;
		if( p_pWindow == JAM_NULL )
		{
			return JAM_FAIL;
		}

		m_pWindow = p_pWindow;

		m_GLContext = SDL_GL_CreateContext( m_pWindow );
		
		if( m_GLContext == JAM_NULL )
		{
			std::cout << "[Jam::Renderer::Initialise] <ERROR> Failed to "
				"create an OpenGL context" << std::endl;

			return JAM_FAIL;
		}

		glewExperimental = GL_TRUE;
		GLenum GLEWError = glewInit( );

		if( GLEWError != GLEW_OK )
		{
			std::cout << "[Jam::Renderer::Initialise] <ERROR> Failed to "
				"initialise GLEW" << std::endl;

			return JAM_FAIL;
		}

		// Initialising GLEW generates an error, this is used to ensure the
		// error doesn't propagate downward
		glGetError( );

		GLint GLMajor, GLMinor;
		glGetIntegerv( GL_MAJOR_VERSION, &GLMajor );
		glGetIntegerv( GL_MINOR_VERSION, &GLMinor );

		std::cout << "[Jam::Renderer::Initialise] <INFO> OpenGL Version: " <<
			GLMajor << "." << GLMinor << std::endl;
		
		std::cout << "[Jam::Renderer::Initialise] <INFO> OpenGL Vendor: " <<
			glGetString( GL_VENDOR ) << std::endl;

		std::cout << "[Jam::Renderer::Initialise] <INFO> OpenGL "
			"Renderer: " << glGetString( GL_RENDERER ) << std::endl;

		std::cout << "[Jam::Renderer::Initialise] <INFO> GLSL Version: " <<
			glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

		std::cout << "[Jam::Renderer::Initialise] <INFO> GLEW Version: " <<
			glewGetString( GLEW_VERSION ) << std::endl;

		std::cout << "[Jam::Renderer::Initialise] <INFO> Checking for "
			"required OpenGL extensions" << std::endl;

		std::cout << "\tARB_texture_storage... ";
		if( GLEW_ARB_texture_storage == GL_TRUE )
		{
			std::cout << "[OK]" << std::endl;
		}
		else
		{
			std::cout << "[!!]" << std::endl;
			return JAM_FAIL;
		}

		glGenFramebuffers( 1, &m_Framebuffer );
		glBindFramebuffer( GL_FRAMEBUFFER, m_Framebuffer );

		glGenTextures( sizeof( m_GBuffer ) / sizeof( m_GBuffer[ 0 ] ), m_GBuffer );
		glGenTextures( 1, &m_DepthTexture );


		for( JAM_MEMSIZE i = 0; i < sizeof( m_GBuffer ) / sizeof( m_GBuffer[ 0 ] ); ++i )
		{
			glBindTexture( GL_TEXTURE_2D, m_GBuffer[ i ] );
			/*glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, 800, 600, 0, GL_RGBA,
				GL_FLOAT, JAM_NULL );*/
			glTexStorage2D( GL_TEXTURE_2D, 1, GL_RGBA32F, 800, 600 );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST );
			glFramebufferTexture2D( GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_GBuffer[ i ], 0 );
		}

		glBindTexture( GL_TEXTURE_2D, m_DepthTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 800, 600, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, JAM_NULL );
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, m_DepthTexture, 0 );

		GLenum DrawBuffers[ ] =
		{
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2,
			GL_COLOR_ATTACHMENT3
		};

		glDrawBuffers( sizeof( DrawBuffers ) / sizeof( DrawBuffers[ 0 ] ),
			DrawBuffers );

		Error = glCheckFramebufferStatus( GL_FRAMEBUFFER );

		if( Error != GL_FRAMEBUFFER_COMPLETE )
		{
			std::cout << "[Jam::Renderer::Initialise] <ERROR> Framebuffer "
				"creation error: 0x" << std::hex <<
				static_cast< int >( Error ) << std::dec << std::endl;
			return JAM_FAIL;
		}

		glBindFramebuffer( GL_FRAMEBUFFER, 0 );

		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glViewport( 0, 0, 800, 600 );

		m_pPolygonCache = new PolygonCache( );

		return JAM_OK;
	}

	JAM_UINT32 Renderer::GBufferBegin( )
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_Framebuffer );

		glClearColor( 0.32f, 0.0f, 0.32f, 1.0f );

		glDepthMask( GL_TRUE );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glEnable( GL_DEPTH_TEST );
		glDisable( GL_BLEND );

		return JAM_OK;
	}

	void Renderer::GBufferEnd( )
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

		glViewport( 0, 0, 800, 600 );

		glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBindFramebuffer( GL_READ_FRAMEBUFFER, m_Framebuffer );

		GLsizei HalfWidth = 400;
		GLsizei HalfHeight = 300;

		// Position
		glReadBuffer( GL_COLOR_ATTACHMENT0 );
		glBlitFramebuffer( 0, 0, 800, 600,
			0, HalfHeight, 400, 600,
			GL_COLOR_BUFFER_BIT, GL_LINEAR );

		// Albedo
		glReadBuffer( GL_COLOR_ATTACHMENT1 );
		glBlitFramebuffer( 0, 0, 800, 600,
			HalfWidth, HalfHeight, 800, 600,
			GL_COLOR_BUFFER_BIT, GL_LINEAR );

		// Normals
		glReadBuffer( GL_COLOR_ATTACHMENT2 );
		glBlitFramebuffer( 0, 0, 800, 600,
			0, 0, HalfWidth, HalfHeight, 
			GL_COLOR_BUFFER_BIT, GL_LINEAR );

		glDepthMask( GL_FALSE );

		glDisable( GL_DEPTH_TEST );

		glBindFramebuffer( GL_FRAMEBUFFER, 0 );

		// TESTING!
		//g_Sphere.Render( *this );
	}

	JAM_UINT32 Renderer::BeginLightPass( )
	{
		glEnable( GL_BLEND );
		glBlendEquation( GL_FUNC_ADD );
		glBlendFunc( GL_ONE, GL_ONE );

		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_Framebuffer );

		glClear( GL_COLOR_BUFFER_BIT );

	}

	JAM_UINT32 Renderer::RegisterPolygons( const MemSize p_VertexCount,
		const JAM_MEMSIZE p_IndexCount, const JAM_BYTE *p_pVertices,
		const JAM_UINT16 *p_pIndices, const GLenum p_PrimitiveType,
		const JAM_UINT64 p_VertexAttributes, JAM_UINT32 &p_CacheID )
	{
		std::cout << "VC: " << p_VertexCount << std::endl;
		std::cout << "IC: " << p_IndexCount << std::endl;
		return m_pPolygonCache->AddPolygons( p_VertexCount, p_IndexCount,
			p_pVertices, p_pIndices, p_PrimitiveType, p_VertexAttributes,
			p_CacheID );
	}

	JAM_UINT32 Renderer::RenderPolygons( const JAM_UINT32 p_CacheID )
	{
		return m_pPolygonCache->Render( p_CacheID );
	}

	void Renderer::SetClearColour( const JAM_FLOAT32 p_Red,
		const JAM_FLOAT32 p_Green, const JAM_FLOAT32 p_Blue )
	{
		glClearColor( p_Red, p_Green, p_Blue, 1.0f );
	}

	void Renderer::Clear( const JAM_BOOL p_ColourBuffer,
		const JAM_BOOL p_DepthBuffer, const JAM_BOOL p_StencilBuffer )
	{
		GLbitfield Flags = 0;

		if( p_ColourBuffer )
		{
			Flags |= GL_COLOR_BUFFER_BIT;
		}

		if( p_DepthBuffer )
		{
			Flags |= GL_STENCIL_BUFFER_BIT;
		}

		if( p_StencilBuffer )
		{
			Flags |= GL_STENCIL_BUFFER_BIT;
		}

		glClear( Flags );
	}

	void Renderer::SwapBuffers( )
	{
		SDL_GL_SwapWindow( m_pWindow );		
	}
}

