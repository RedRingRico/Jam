#ifndef __JAM_TESTGAMESTATE_HPP__
#define __JAM_TESTGAMESTATE_HPP__

#include <DataTypes.hpp>
#include <GameState.hpp>

namespace Jam
{
	class TestGameState : public GameState
	{
	public:
		TestGameState( );
		virtual ~TestGameState( );

		ErrorCode Initialise( ) override;
		ErrorCode Load( ) override;
		ErrorCode Update( ) override;
		ErrorCode Render( ) override;
		ErrorCode Unload( ) override;
		ErrorCode Terminate( ) override;

	private:
	};
}

#endif // __JAM_TESTGAMESTATE_HPP__
