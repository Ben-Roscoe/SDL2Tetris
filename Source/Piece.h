#pragma once

#include "Block.h"

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

enum class PieceRotation
{
	Right,
	Left,
};

const int PieceWidth	= 4;
const int PieceHeight	= 4;
const int MaxSpace		= 4;

struct PieceFormation
{
	Block	blocks[PieceWidth][PieceHeight];
	int		space;
};

struct Piece
{
	unsigned int	x;
	unsigned int	y;
	float			nextFall;
	bool			active;
	bool			isFalling;

	PieceFormation	formation;
};


void Piece_New( Piece& piece );
void Piece_Destroy( Piece& piece );
void Piece_Tick( Piece& piece, float deltaTime );
void Piece_Rotate( Piece& piece, PieceRotation rotation );
void Piece_StopFalling( Piece& piece );
void PieceFormation_SetColour( PieceFormation& pieceFormation, uint32_t colour );
void PieceFormation_Draw( const PieceFormation& pieceFormation, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin );