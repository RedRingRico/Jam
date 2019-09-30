
#ifndef __JAM_DATATYPES_HPP__
#error This file should not be included directly (Compiler_GCC.hpp).  Include DataTypes.hpp, instead.
#endif // __JAM_DATATYPES_HPP__

#ifndef __JAM_COMPILER_GCC_HPP__
#define __JAM_COMPILER_GCC_HPP__

#if __cplusplus <= 199711L
#error Unsupported compiler (C++11 required)
#else
#include <cstddef>
#include <cstdint>
#include <endian.h>

namespace Jam
{
	typedef signed char		SChar8;
	typedef unsigned char	UChar8;
	typedef std::int8_t		SInt8;
	typedef std::uint8_t	UInt8;
	typedef std::int16_t	SInt16;
	typedef std::uint16_t	UInt16;
	typedef std::int32_t	SInt32;
	typedef std::uint32_t	UInt32;
	typedef std::int64_t	SInt64;
	typedef std::uint64_t	UInt64;
	typedef std::size_t		MemSize;

#define NullPtr nullptr
}

#define JAM_COMPILER_VERSION ( __GNUc__ * 10000 + __GNUC_MINOR__ * 100 + \
	__GNUC_PATCHLEVEL__ )

#define JAM_COMPILER_GCC

#define JAM_PACKDATA_BEGIN( p_Align )
#define JAM_PACKDATA_END( p_Align ) __attribute__( ( __aligned( p_Align ) ) )

#define JAM_INLINE __inline__
#define JAM_FORCE_INLINE __forceinline__

#define JAM_EXPLICIT explicit
#define JAM_ASM __asm__

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define JAM_LITTLE_ENDIAN
#else
#define JAM_BIG_ENDIAN
#endif // __BYTE_ORDER

#endif // __cplusplus <= 199711L

#endif // __JAM_COMPILER_GCC_HPP__
