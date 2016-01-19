#include "Line.h"


bool Line_IsCleared( const Line& line )
{
	for( int i = 0; i < LineWidth; ++i )
	{
		if( !line.blocks[i].active )
		{
			return false;
		}
	}
	return true;
}


void Line_Deactivate( Line& line )
{
	for( int i = 0; i < LineWidth; ++i )
	{
		line.blocks[i].active = false;
	}
}


void Line_Tick( Line& line, float deltaTime )
{
	for( int i = 0; i < LineWidth; ++i )
	{
		Block_Tick( line.blocks[i], deltaTime );
	}
}