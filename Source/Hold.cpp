#include "Hold.h"
#include "Block.h"
#include "Piece.h"


PieceFormation* Hold_HoldFormation( Hold& hold, PieceFormation* formation )
{
	auto temp				= hold.heldFormation;
	hold.heldFormation		= formation;
	hold.canHold			= false;
	return temp;
}


void Hold_ResetHold( Hold& hold )
{
	hold.canHold = true;
}


bool Hold_CanHold( Hold& hold )
{
	return hold.canHold;
}


void Hold_Clear( Hold& hold )
{
	hold.canHold			= true;
	hold.heldFormation		= nullptr;
}


void Hold_Draw( Hold& hold, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin )
{
	SDL_Rect dst = origin;
	dst.w		 = BlockWidth;
	dst.h		 = BlockHeight;

	SDL_SetTextureColorMod( blockTexture, 0x7F, 0x7F, 0x7F );
	for( int i = 0; i <= HoldBorderWidth; ++i )
	{
		dst.x = origin.x + ( i * BlockWidth );

		dst.y = origin.y;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );

		dst.y = origin.y + ( BlockHeight * HoldBorderHeight );
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );
	}

	for( int i = 0; i <= HoldBorderHeight; ++i )
	{
		dst.y = origin.y + ( i * BlockHeight );

		dst.x = origin.x;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );

		dst.x = origin.x + ( BlockWidth * HoldBorderWidth );
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );
	}

	// Draw the held shape.
	if( hold.heldFormation != nullptr )
	{
		SDL_Rect formationOrigin;
		formationOrigin.x = origin.x + BlockWidth * 2;
		formationOrigin.y = origin.y + BlockHeight * 2;
		PieceFormation_Draw( *hold.heldFormation, renderer, blockTexture, formationOrigin );
	}
}