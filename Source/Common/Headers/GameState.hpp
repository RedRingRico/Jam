#ifndef __JAM_GAMESTATE_HPP__
#define __JAM_GAMESTATE_HPP__

#include <DataTypes.hpp>

namespace Jam
{
	class GameState
	{
	public:
		virtual ~GameState( );

		virtual ErrorCode Load( ) = 0;
		virtual ErrorCode Unload( ) = 0;
		virtual ErrorCode Update( ) = 0;
		virtual ErrorCode Render( ) = 0;
		virtual ErrorCode Initialise( ) = 0;
		virtual ErrorCode Terminate( ) = 0;

		Bool IsPaused( ) const;
		void Pause( );
		void Resume( );

	private:
		GameState( ){ }

	protected:
		Bool	m_Paused;
	};
}

#endif // __JAM_GAMESTATE_HPP__
