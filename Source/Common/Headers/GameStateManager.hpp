#ifndef __JAM_GAMESTATEMANAGER_HPP__
#define __JAM_GAMESTATEMANAGER_HPP__

#include <DataTypes.hpp>
#include <string>
#include <map>
#include <vector>

namespace Jam
{
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager( );
		~GameStateManager( );

		ErrorCode RegisterGameState( const std::string &p_StateName,
			GameState *p_pGameState );

		ErrorCode Execute( );

	private:
		std::map< std::string, GameState * >	m_GameStateRegistry;
		std::vector< GameState * >				m_GameStateStack;
	};
}

#endif // __JAM_GAMESTATEMANAGER_HPP__
