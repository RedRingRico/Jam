#ifndef __JAM_DATATYPES_HPP__
#error This file should not be included directly (DataTypes_Linux.hpp).  Include DataTypes.hpp, instead.
#endif // __JAM_DATATYPES_HPP__

#ifndef __JAM_DATATYPES_LINUX_HPP__
#define __JAM_DATATYPES_LINUX_HPP__

#include <cstdio>

namespace Jam
{
	typedef std::FILE	*FileHandle;
	typedef int			FileDescriptor;
	typedef void		*LibraryHandle;

	extern const decltype( NullPtr ) InvalidFileHandle;
	extern const int InvalidFileDescriptor;
	extern const decltype( NullPtr ) InvalidLibraryHandle;
}

#endif // __JAM_DATATYPES_LINUX_HPP__

