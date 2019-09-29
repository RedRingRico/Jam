#ifndef __JAM_DATATYPES_HPP__
#define __JAM_DATATYPES_HPP__

#include <cstdint>
#include <cstddef>

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

#endif // __JAM_DATATYPES_HPP__

