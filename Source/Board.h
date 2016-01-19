#pragma once

#include "Piece.h"
#include "Line.h"
#include "Level.h"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Point;

struct Mix_Chunk;

struct Hold;
struct Score;

const float			LineFallSpeed	= 700.0f;
const float			LineFadeSpeed	= 700.0f;

const float			InitialFallTime = 0.7f;
const unsigned int	MaxPieces		= 2;

const int   PieceStartX		= 4;
const int	PieceStartY		= 0;
const int	BoardHeight		= 20;

const float BoardGameOverEffectBlockTime = 0.015f;

enum class BoardState
{
	Live,
	ClearFading,
	ClearFalling,
	GameOverEffect,
	GameOver,
	StartGameEffect,
};


struct Board
{
	float		fallTime;
	Piece		pieces[MaxPieces];
	Line		lines[BoardHeight];
	BoardState	state;

	float		currentFallDistance;

	uint8_t		targetClearAlpha;
	uint8_t		currentClearAlpha;

	float		currentGameOverEffectBlockTime  = 0.0f;
	int			lastGameOverEffectBlockX		= -1;
	int			lastGameOverEffectBlockY		= -1;
};


void Board_New( Board& board );
void Board_Tick( Board& board, float deltaTime, Hold* hold, Score* score, Level* level,
				 Mix_Chunk* pieceFallSound, Mix_Chunk* singleDoubleClearSound,
				 Mix_Chunk* tripleClearSound, Mix_Chunk* tetrisClearSound,
				 Mix_Chunk* softDropSound );
void Board_Draw( Board& board, SDL_Renderer* renderer, SDL_Texture* blockTexture,
					const SDL_Point& origin );
bool Board_TryPieceFall( Board& board, Piece& piece, Score* score, Level* level,
						Mix_Chunk* singleDoubleClearSound, Mix_Chunk* tripleClearSound,
						Mix_Chunk* tetrisClearSound );
bool Board_AdjustPiecePosition( Board& board, Piece& piece, int deltaX, int deltaY );
void Board_DropPiece( const Board& board, Piece& piece );
bool Board_RotatePiece( Board& board, Piece& piece, PieceRotation rotation );
bool Board_NewPiece( Board& board, const PieceFormation& formation );
void Board_DestroyPiece( Board& board, Piece& piece, Score* score, Level* level,
						Mix_Chunk* singleDoubleClearSound, Mix_Chunk* tripleClearSound,
						Mix_Chunk* tetrisClearSound );
void Board_Reset( Board& board );
Piece* Board_GetFirstFallingPiece( Board& board );
bool Board_IsPieceFalling( Board& board );

void Board_RemovePiece( Board& board, const Piece& piece );
void Board_AddPiece( Board& board, const Piece& piece );