#include <GameState.hpp>

namespace Jam
{
	GameState::GameState( ) :
		m_Paused( False )
	{
	}

	GameState::~GameState( )
	{
	}

	Bool GameState::IsPaused( ) const
	{
		return m_Paused;
	}

	void GameState::Pause( )
	{
		m_Paused = True;
	}

	void GameState::Resume( )
	{
		m_Paused = False;
	}

	void GameState::SetGameStateManager( GameStateManager &p_GSM )
	{
		m_GameStateManager = p_GSM;
	}
}
