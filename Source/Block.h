#pragma once

#include <stdint.h>


const uint32_t	RedMask		= 0x00FF0000;
const uint32_t	GreenMask	= 0x0000FF00;
const uint32_t	BlueMask	= 0x000000FF;

const uint32_t  BlockFlashColour = 0x00FFFFFF;

const float		BlockFlashTime	 = 0.1f;

const int	BlockWidth		= 23;
const int	BlockHeight		= 23;

struct Block
{
	bool		active;
	uint32_t	colour;

	bool		isFlashing			= false;
	float		currentFlashTime	= 0.0f;
	uint32_t	unflashColour;
};


void Block_StartFlash( Block& block );
void Block_EndFlash( Block& block );
void Block_Tick( Block& block, float deltaTime );