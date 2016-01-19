#include "Game.h"
#include <iostream>
Game game;

int main( int argc, char** argv )
{
	Game_New( game );
	Game_Run( game );
	Game_Destroy( game );
	return 0;
}