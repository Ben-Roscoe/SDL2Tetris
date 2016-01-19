#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "ScoreBoard.h"

struct GameOverDisplay
{
	ScoreBoard				scoreBoard;

	SDL_Texture*			gameOverTexture	= nullptr;
	SDL_Point				gameOverTextureSize;

	SDL_Texture*			continueTexture	= nullptr;
	SDL_Point				continueTextureSize;

	SDL_Texture*			highScoreTexture		= nullptr;
	SDL_Point				hightScoreTextureSize;	
	bool					isHighScorer	= false;
};



void GameOverDisplay_New( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, TTF_Font* font, const char* scoreBoardFileName );
void GameOverDisplay_Destroy( GameOverDisplay& gameOverDisplay, const char* scoreBoardFileName );
void GameOverDisplay_Draw( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, const SDL_Point& origin );