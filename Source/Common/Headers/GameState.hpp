#ifndef __JAM_GAMESTATE_HPP__
#define __JAM_GAMESTATE_HPP__

#include <DataTypes.hpp>
#include <GameStateManager.hpp>

namespace Jam
{
	class GameState
	{
	public:
		GameState( );
		virtual ~GameState( );

		virtual ErrorCode Initialise( ) = 0;
		virtual ErrorCode Load( ) = 0;
		virtual ErrorCode Update( ) = 0;
		virtual ErrorCode Render( ) = 0;
		virtual ErrorCode Unload( ) = 0;
		virtual ErrorCode Terminate( ) = 0;

		Bool IsPaused( ) const;
		void Pause( );
		void Resume( );
		void SetGameStateManager( GameStateManager &p_GSM );

	private:

	protected:
		Bool				m_Paused;
		GameStateManager	m_GameStateManager;
	};
}

#endif // __JAM_GAMESTATE_HPP__
