#include <GameState.hpp>

namespace Jam
{
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
}
