#ifndef __JAM_GAME_HPP__
#define __JAM_GAME_HPP__

#include <DataTypes.hpp>
#include <SDL2/SDL.h>
#include <Renderer.hpp>

namespace Jam
{
	class Game
	{
	public:
		Game( );
		~Game( );

		JAM_UINT32 Initialise( );

		JAM_UINT32 Execute( );

	private:
		JAM_UINT32 PlatformInitialise( );

		Renderer	m_Renderer;

		SDL_Window		*m_pWindow;
	};
}

#endif // __JAM_GAME_HPP__

