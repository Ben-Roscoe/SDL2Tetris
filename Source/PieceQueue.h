#pragma once

#include "Piece.h"


const int PieceQueueSize  = 5;
const int PieceQueueWidth = 6;

struct PieceQueue
{
	PieceFormation*			queue[PieceQueueSize];
};


void PieceQueue_New( PieceQueue& pieceQueue );
PieceFormation* PieceQueue_PushBack( PieceQueue& pieceQueue, PieceFormation* formation );
void PieceQueue_Clear( PieceQueue& pieceQueue );
void PieceQueue_Draw( PieceQueue& pieceQueue, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin );