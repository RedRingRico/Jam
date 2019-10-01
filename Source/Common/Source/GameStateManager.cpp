#include <GameStateManager.hpp>
#include <GameState.hpp>

namespace Jam
{
	GameStateManager::GameStateManager( )
	{
	}

	GameStateManager::~GameStateManager( )
	{
	}

	ErrorCode GameStateManager::RegisterGameState( const std::string &p_StateName,
		GameState *p_pGameState )
	{
		if( p_pGameState == NullPtr )
		{
			return ErrorCode::FatalError;
		}

		m_GameStateRegistry[ p_StateName ] = p_pGameState;

		return ErrorCode::Okay;
	}

	ErrorCode GameStateManager::Execute( )
	{
		while( m_GameStateStack.empty( ) == false )
		{
			UInt32 StatesProcessed = 0;
			// Work back-to-front through the stack, if a state is paused, don't update
			for( auto State : m_GameStateStack )
			{
				if( State->IsPaused( ) )
				{
					break;
				}
				++StatesProcessed;
			}

			if( StatesProcessed == 0 )
			{
				return ErrorCode::FatalError;
			}
		}

		return ErrorCode::Okay;
	}
}
