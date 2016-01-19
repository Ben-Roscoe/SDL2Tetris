#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

const int MaxHighScores	= 5;

struct ScoreBoardEntry
{
	int				score		= 0;
	SDL_Texture*	texture		= nullptr;
	SDL_Point		size;
};


struct ScoreBoard
{
	ScoreBoardEntry			highScores[MaxHighScores];

	SDL_Texture*			texture			= nullptr;
	SDL_Point				textureSize;
};


void ScoreBoardEntry_New( ScoreBoardEntry& scoreBoardEntry, int score, int position, SDL_Renderer* renderer, TTF_Font* font );
void ScoreBoardEntry_SetScorePosition( ScoreBoardEntry& scoreBoardEntry, int score, int position, SDL_Renderer* renderer, TTF_Font* font );
void ScoreBoardEntry_Destroy( ScoreBoardEntry& scoreBoardEntry );

void ScoreBoard_Load( ScoreBoard& scoreBoard, const char* fileName, SDL_Renderer* renderer, TTF_Font* font );
void ScoreBoard_Save( const ScoreBoard& scoreBoard, const char* fileName );
bool ScoreBoard_Submit( ScoreBoard& scoreBoard, int score, SDL_Renderer* renderer, TTF_Font* font );
void ScoreBoard_Destroy( ScoreBoard& scoreBoard );
int ScoreBoard_Draw( ScoreBoard& scoreBoard, SDL_Renderer* renderer, const SDL_Point& origin );