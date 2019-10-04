#include <GameStateManager.hpp>
#include <GameState.hpp>
#include <iostream>

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
		m_GameStateRegistry[ p_StateName ]->SetGameStateManager( *this );

		std::cout << "State registered" << std::endl;

		return ErrorCode::Okay;
	}

	ErrorCode GameStateManager::Execute( )
	{
		while( m_GameStateStack.empty( ) == false )
		{
		std::cout << "State count: " << m_GameStateStack.size( ) << std::endl;
			UInt32 StatesProcessed = 0;

			// Work back-to-front through the stack, if a state is paused, don't update
			for( auto State : m_GameStateStack )
			{
				if( State->IsPaused( ) )
				{
					break;
				}

				State->Update( );

				m_Renderer.Clear( JAM_TRUE, JAM_TRUE, JAM_TRUE );
				State->Render( );
				m_Renderer.SwapBuffers( );

				++StatesProcessed;
			}
			//std::cout << "States processed: " << StatesProcessed << std::endl;

			if( StatesProcessed == 0 )
			{
				std::cout << "[Jam::GameStateManager::Execute] <ERROR> No states processed" <<
					std::endl;
				return ErrorCode::FatalError;
			}

			//std::cout << "empty: " << m_GameStateStack.empty( ) << std::endl;
		}

		std::cout << "Done" << std::endl;

		return ErrorCode::Okay;
	}

	ErrorCode GameStateManager::ChangeState( const std::string &p_StateName )
	{
		auto Entry = m_GameStateRegistry.find( p_StateName );

		if( Entry == m_GameStateRegistry.end( ) )
		{
			std::cout << "[Jam::GameStateManager::ChangeState] <ERROR> State: \"" <<
				p_StateName << "\" not registered" << std::endl;

			return ErrorCode::FatalError;
		}

		while( PopState( ) != NullPtr )
		{
			std::cout << "Popping state" << std::endl;
		}

		std::cout << "Pushing state" << std::endl;

		return PushState( p_StateName );
	}

	ErrorCode GameStateManager::PushState( const std::string &p_StateName )
	{
		auto Entry = m_GameStateRegistry.find( p_StateName );

		if( Entry == m_GameStateRegistry.end( ) )
		{
			std::cout << "[Jam::GameStateManager::PushState] <ERROR> State: \"" <<
				p_StateName << "\" not registered" << std::endl;

			return ErrorCode::FatalError;
		}

		m_GameStateStack.push_back( Entry->second );
		Entry->second->Initialise( );
		Entry->second->Load( );

		std::cout << "State pushed" << std::endl;
		std::cout << "State count: " << m_GameStateStack.size( ) << std::endl;
		if ( m_GameStateStack.empty( ) )
		{
			std::cout << "something's fucked" << std::endl;
		}

		return ErrorCode::Okay;
	}

	GameState *GameStateManager::PopState( )
	{
		std::cout << "Popping state" << std::endl;
		std::cout << "State count: " << m_GameStateStack.size( ) << std::endl;
		if( m_GameStateStack.empty( ) == false )
		{
			GameState *pReturn = m_GameStateStack.back( );
			pReturn->Unload( );
			pReturn->Terminate( );
			m_GameStateStack.pop_back( );

			std::cout << "State popped!" << std::endl;

			return pReturn;
		}

		std::cout << "No more states!" << std::endl;
		return NullPtr;
	}

	void GameStateManager::Quit( )
	{
		GameState *pState = PopState( );
			//std::cout << "pState: " << pState << std::endl;
		while( pState != NullPtr )
		{
			std::cout << "pState: " << pState << std::endl;
			std::cout << "Popping state" << std::endl;
			pState = PopState( );
		}
		std::cout << "quitting..." << std::endl;
		std::cout << "State count: " << m_GameStateStack.size( ) << std::endl;
	}

	Renderer *GameStateManager::GetRenderer( )
	{
		return &m_Renderer;
	}
}
