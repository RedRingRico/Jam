#include <iostream>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Red Ring Rico's Game Jam Framework" << std::endl;

	Jam::Game TheGame;

	if( TheGame.Initialise( ) != JAM_OK )
	{
		std::cout << "[main] <ERROR> Something went wrong initialising the game" << std::endl;

		return JAM_FAIL;
	}

	return TheGame.Execute( );
}

