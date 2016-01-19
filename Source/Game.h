#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "UserCmd.h"
#include "Board.h"
#include "Hold.h"
#include "PieceQueue.h"
#include "Score.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameOverDisplay.h"
#include "Level.h"

const double	MaxFramePeriod		= 1.0 / 60.0;
const int		TotalTetrisPieces	= 7;

enum class GameState
{
	MainMenu,
	Playing,
	Paused,
	GameOver,
};


struct Game
{
	SDL_Window*		window;
	SDL_Renderer*	renderer;

	UserCmd			userCmd;

	Board			board;
	Hold			hold;
	PieceQueue		pieceQueue;
	Score			score;
	MainMenu		mainMenu;
	PauseMenu		pauseMenu;
	GameOverDisplay gameOverDisplay;
	Level			level;

	SDL_Texture*	blockTexture;
	TTF_Font*		font;

	// Array of all tetris pieces.
	PieceFormation  pieceBlocks[TotalTetrisPieces];
	PieceFormation* currentFormation;

	PieceFormation* randomPiecePool[TotalTetrisPieces];
	int				randomPiecesLeft = 0;
	bool			spawnLinePiece	 = true;

	GameState		gameState		 = GameState::MainMenu;
	bool			quit			 = false;


	// Sounds.
	Mix_Chunk*		pieceFallSound		= nullptr;
	Mix_Chunk*		pieceHoldSound		= nullptr;
	Mix_Chunk*		pieceRotateSound	= nullptr;
	Mix_Chunk*		pieceSoftDropSound	= nullptr;
	Mix_Chunk*		pieceHardDropSound	= nullptr;

	Mix_Chunk*		menuHighlightChanegSound = nullptr;
	Mix_Chunk*		menuSelectedSound		 = nullptr;

	Mix_Chunk*		clearSingleDoubleSound	= nullptr;
	Mix_Chunk*		clearTripleSound		= nullptr;
	Mix_Chunk*		clearTetrisSound		= nullptr;

	Mix_Music*		inGameMusic				= nullptr;
};


SDL_Point Game_GetResoltuion( Game& game );

void Game_New( Game& game );
void Game_Run( Game& game );
void Game_Destroy( Game& game );

void Game_Tick( Game& game, float deltaTime );
void Game_Draw( Game& game );