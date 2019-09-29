#ifndef __JAM_TEXTURE_HPP__
#define __JAM_TEXTURE_HPP__

#include <DataTypes.hpp>
#include <MD5.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <hl_md5.h>
#include <string>

namespace Jam
{
	// Currently, only Targa files are handled at all
#pragma pack( 1 )
	typedef struct _tagTARGA_HEADER
	{
		JAM_BYTE	IDLength;
		JAM_BYTE	ColourmapType;
		JAM_BYTE	ImageType;
		JAM_BYTE	ColourmapSpecification[ 5 ];
		JAM_UINT16	X;
		JAM_UINT16	Y;
		JAM_UINT16	Width;
		JAM_UINT16	Height;
		JAM_BYTE	BitsPerPixel;
		JAM_BYTE	ImageDescription;
	}TARGA_HEADER,*PTARGA_HEADER;
#pragma pack( )

	class Shader;

	class Texture
	{
	public:
		Texture( );
		~Texture( );

		JAM_UINT32 LoadFromFile( const std::string &p_FileName );

		void SetActive( Shader *p_pShader );

		JAM_UINT32 GetDigest( MD5_DIGEST &p_Digest ) const;

	private:
		MD5_DIGEST	m_Digest;
		MD5			m_MD5;
		HL_MD5_CTX	m_MD5Context;
		GLuint		m_TextureID;
		GLuint		m_SamplerID;
	};
}

#endif // __JAM_TEXTURE_HPP__

