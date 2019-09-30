#ifndef __JAM_DATATYPES_HPP__
#define __JAM_DATATYPES_HPP__

#if defined ( __GNUC__ )
#include <Compiler_GCC.hpp>
#endif // __GNUC__

typedef unsigned char	JAM_BYTE;
typedef unsigned char	JAM_UCHAR;
typedef signed char		JAM_SCHAR;
typedef int8_t			JAM_SINT8;
typedef uint8_t			JAM_UINT8;
typedef int16_t			JAM_SINT16;
typedef uint16_t		JAM_UINT16;
typedef int32_t			JAM_SINT32;
typedef uint32_t		JAM_UINT32;
typedef int64_t			JAM_SINT64;
typedef uint64_t		JAM_UINT64;

typedef JAM_UINT32	JAM_BOOL;
typedef size_t		JAM_MEMSIZE;
typedef float		JAM_FLOAT32;
typedef double		JAM_FLOAT64;

#define JAM_NULL nullptr

#define JAM_EXPLICIT explicit

const JAM_UINT32 JAM_OK		= 0x00000000;
const JAM_UINT32 JAM_FAIL	= 0xFFFFFFFF;

const JAM_BOOL JAM_TRUE		= 1;
const JAM_BOOL JAM_FALSE	= 0;

typedef struct _tagFILE_CHUNK
{
	JAM_UINT32	ID;
	JAM_UINT32	Size;
}FILE_CHUNK,*PFILE_CHUNK;

const JAM_UINT32 FILE_END_CHUNK	= 0xFFFFFFFF;

// Compiler-agnostic data types
namespace Jam
{
	typedef float	Float32;
	typedef double	Float64;

	typedef UInt8	Byte;
	typedef MemSize	Bool;

	const Bool True = 1;
	const Bool False = 0;
}

#include <ErrorCodes.hpp>

#if defined ( __linux__ )
#include <DataTypes_Linux.hpp>
#else
#error No platform detected
#endif // __linux__

#include <string>

namespace Jam
{
	ErrorCode GetCompilerString( std::string &p_CompilerString );

	// Endian swapping
	JAM_INLINE UInt16 SwapEndianUInt16( UInt16 p_Swap )
	{
		return	( ( p_Swap & 0x00FF ) << 8 ) |
				( ( p_Swap & 0xFF00 ) >> 8 );
	}

	JAM_INLINE UInt32 SwapEndianUInt32( UInt32 p_Swap )
	{
		return	( ( p_Swap & 0x000000FF << 24 ) |
				( ( p_Swap & 0x0000ff00 ) << 8 ) |
				( ( p_Swap & 0x00FF0000 ) >> 8 ) |
				( ( p_Swap & 0xFF000000 ) >> 24 ) );
	}

#define Align( p_Memory, p_Size ) \
	( ( ( MemSize )( p_Memory ) + ( p_Size ) - 1 ) & \
	( ~( ( p_Size ) - 1 ) ) )
#define AlignUp( p_Memory, p_Size ) ( Align( ( p_Memory ), p_Size ) + \
	( p_Size ) )

#if defined ( JAM_LITTLE_ENDIAN )
#define EndianToBigUInt16( p_Swap ) SwapEndianUInt16( p_Swap )
#define EndianToLittleUInt16( p_Swap )
#define EndianToBigUInt32( p_Swap ) SwapEndianUInt32( p_Swap )
#define EndianToLittleUInt32( p_Swap )
#elif defined ( JAM_BIG_ENDIAN )
#define EndianToBigUInt16( p_Swap )
#define EndianToLittleUInt16( p_Swap ) SwapEndianUInt16( p_Swap )
#define EndianToBigUInt32( p_Swap )
#define EndianToLittleUInt32( p_Swap ) SwapEndianUInt32( p_Swap )
#else
#error No endianness defined
#endif // JAM_LITTLE_ENDIAN
}

#endif // __JAM_DATATYPES_HPP__

