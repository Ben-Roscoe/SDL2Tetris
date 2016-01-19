#pragma once

#include "Block.h"

const int			LineWidth = 10;

const uint32_t		LineFlagFalling = 1;
const uint32_t		LineFlagFading	= 2;

struct Line
{
	Block		blocks[LineWidth];
	uint32_t	lineFlags			= 0;
};


bool Line_IsCleared( const Line& line );
void Line_Deactivate( Line& line );
void Line_Tick( Line& line, float deltaTime );