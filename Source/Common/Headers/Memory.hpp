#ifndef __JAM_MEMORY_HPP__
#define __JAM_MEMORY_HPP__

#include <DataTypes.hpp>

namespace Jam
{
	template< typename T >
	void SafeDelete( T *&p_pPointer )
	{
		if( p_pPointer )
		{
			delete p_pPointer;
			p_pPointer = JAM_NULL;
		}
	}

	template< typename T >
	void SafeDeleteArray( T *&p_pPointer )
	{
		if( p_pPointer )
		{
			delete [ ] p_pPointer;
			p_pPointer = JAM_NULL;
		}
	}
}

#endif // __JAM_MEMORY_HPP__

