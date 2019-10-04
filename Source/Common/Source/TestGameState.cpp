#include <TestGameState.hpp>
#include <iostream>

namespace Jam
{
	TestGameState::TestGameState( )
	{
	}

	TestGameState::~TestGameState( )
	{
	}

	ErrorCode TestGameState::Initialise( )
	{
		return ErrorCode::Okay;
	}

	ErrorCode TestGameState::Load( )
	{
		return ErrorCode::Okay;
	}

	ErrorCode TestGameState::Update( )
	{
		SDL_Event Event;

		while( SDL_PollEvent( &Event ) != 0 )
		{
			if( Event.type == SDL_QUIT )
			{
				m_GameStateManager.Quit( );
			}
		}

		const Uint8 *pKeyState = SDL_GetKeyboardState( NULL );

		if( pKeyState[ SDL_SCANCODE_ESCAPE ] )
		{
			m_GameStateManager.Quit( );
		}

		return ErrorCode::Okay;
	}

	ErrorCode TestGameState::Render( )
	{
		return ErrorCode::Okay;
	}

	ErrorCode TestGameState::Unload( )
	{
		return ErrorCode::Okay;
	}

	ErrorCode TestGameState::Terminate( )
	{
		return ErrorCode::Okay;
	}
}
