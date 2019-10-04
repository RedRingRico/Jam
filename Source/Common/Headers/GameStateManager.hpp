#ifndef __JAM_GAMESTATEMANAGER_HPP__
#define __JAM_GAMESTATEMANAGER_HPP__

#include <DataTypes.hpp>
#include <string>
#include <map>
#include <vector>
#include <Renderer.hpp>

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

		ErrorCode ChangeState( const std::string &p_StateName );
		ErrorCode PushState( const std::string &p_StateName );
		GameState *PopState( );

		void Quit( );

		Renderer *GetRenderer( );

	private:
		std::map< std::string, GameState * >	m_GameStateRegistry;
		std::vector< GameState * >				m_GameStateStack;

		Renderer	m_Renderer;
	};
}

#endif // __JAM_GAMESTATEMANAGER_HPP__
