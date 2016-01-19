#pragma once

#include "Piece.h"
#include <SDL.h>


const int			HoldBorderWidth			= 6;
const int			HoldBorderHeight		= 5;

struct Hold
{
	PieceFormation*		heldFormation	= nullptr;
	bool				canHold			= true;
};


// Holds a new formation and returns the currently held one.
PieceFormation* Hold_HoldFormation( Hold& hold, PieceFormation* formation );
void Hold_ResetHold( Hold& hold );
bool Hold_CanHold( Hold& hold );
void Hold_Clear( Hold& hold );
void Hold_Draw( Hold& hold, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin );