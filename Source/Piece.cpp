#include "Piece.h"
#include <memory>
#include <cassert>
#include <SDL.h>

void Piece_New( Piece& piece )
{
	std::memset( piece.formation.blocks, 0, sizeof( piece.formation.blocks ) );
	piece.active			= true;
	piece.formation.space	= 3;
}


void Piece_Destroy( Piece& piece )
{
	piece.active = false;
}


void Piece_Tick( Piece& piece, float deltaTime )
{
	piece.nextFall -= deltaTime;
}


void Piece_Rotate( Piece& piece, PieceRotation rotation )
{
	Block blocks[PieceWidth][PieceHeight];
	std::memset( blocks, 0, sizeof( blocks ) );
	for( int x = 0; x < PieceWidth - ( MaxSpace - piece.formation.space ); ++x )
	{
		for( int y = 0; y < PieceHeight - ( MaxSpace - piece.formation.space ); ++y )
		{
			if( piece.formation.blocks[x][y].active )
			{
				blocks[PieceHeight - ( ( MaxSpace + 1 ) - piece.formation.space ) - y][x] = piece.formation.blocks[x][y];
			}
		}
	}
	std::memcpy( piece.formation.blocks, blocks, sizeof( blocks ) );
}


void Piece_StopFalling( Piece& piece )
{
	piece.isFalling = false;
	piece.nextFall	= 0.0f;
}


void PieceFormation_SetColour( PieceFormation& pieceFormation, uint32_t colour )
{
	for( int x = 0; x < PieceWidth; ++x )
	{
		for( int y = 0; y < PieceHeight; ++y )
		{
			pieceFormation.blocks[x][y].colour = colour;
		}
	}
}


void PieceFormation_Draw( const PieceFormation& pieceFormation, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin )
{
	SDL_Rect dst;
	dst.w = BlockWidth;
	dst.h = BlockHeight;

	for( int x = 0; x < PieceWidth; ++x )
	{
		for( int y = 0; y < PieceHeight; ++y )
		{
			if( pieceFormation.blocks[x][y].active )
			{
				SDL_SetTextureColorMod( blockTexture, ( pieceFormation.blocks[x][y].colour & RedMask ) >> 16,
									( pieceFormation.blocks[x][y].colour & GreenMask ) >> 8,
										pieceFormation.blocks[x][y].colour & BlueMask );
				dst.x = origin.x + x * BlockWidth;
				dst.y = origin.y + y * BlockHeight;
				SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );
			}
		}
	}
}
