#include "Block.h"
#include <cassert>

void Block_StartFlash( Block& block )
{
	assert( block.active );

	block.currentFlashTime = 0.0f;
	block.unflashColour	   = block.colour;
	block.colour		   = BlockFlashColour;
	block.isFlashing	   = true;
}


void Block_EndFlash( Block& block )
{
	block.currentFlashTime	= 0.0f;
	block.colour			= block.unflashColour;
	block.isFlashing		= false;
}


void Block_Tick( Block& block, float deltaTime )
{
	if( block.isFlashing )
	{
		block.currentFlashTime += deltaTime;
		if( block.currentFlashTime >= BlockFlashTime )
		{
			Block_EndFlash( block );
		}
	}
}