#include "Score.h"
#include "Utility.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

const char*			ScoreTitleText  = "Score";
const SDL_Color		ScoreTitleColor = { 0xFF, 0xFF, 0xFF };
const SDL_Color		ScoreColour		= { 0xFF, 0xFF, 0xFF };


static void Score_BuildScoreTexture( Score& score, SDL_Renderer* renderer, TTF_Font* font )
{
	// Get score string.
	char buffer[30];
	sprintf_s( buffer, "%d", score.value );
	Utility_BuildFontTexture( &score.scoreTexture, &score.scoreSize, buffer, ScoreColour,
								renderer, font );
}


void Score_New( Score& score, SDL_Renderer* renderer, TTF_Font* titleFont )
{
	Utility_BuildFontTexture( &score.titleTexture, &score.titleSize, ScoreTitleText, ScoreColour,
								renderer, titleFont );
	Score_BuildScoreTexture( score, renderer, titleFont );
}


void Score_Destroy( Score& score )
{
	if( score.titleTexture != nullptr )
	{
		SDL_DestroyTexture( score.titleTexture );
		score.titleTexture = nullptr;
	}
	if( score.scoreTexture != nullptr )
	{
		SDL_DestroyTexture( score.scoreTexture );
		score.scoreTexture = nullptr;
	}
}


void Score_Add( Score& score, int delta )
{
	score.value += delta;
}


void Score_Clear( Score& score )
{
	score.value = 0;
}


void Score_Draw( Score& score, SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& origin )
{
	if( score.value != score.oldValue )
	{
		Score_BuildScoreTexture( score, renderer, font );
		score.oldValue = score.value;
	}

	SDL_Rect dst;
	dst.x = origin.x - score.titleSize.x / 2.0f;
	dst.y = origin.y - score.titleSize.y / 2.0f;
	dst.w = score.titleSize.x;
	dst.h = score.titleSize.y;
	SDL_RenderCopy( renderer, score.titleTexture, nullptr, &dst );

	dst.x = origin.x - score.scoreSize.x / 2.0f;
	dst.y = origin.y + score.titleSize.y - score.scoreSize.y / 2.0f;
	dst.w = score.scoreSize.x;
	dst.h = score.scoreSize.y;
	SDL_RenderCopy( renderer, score.scoreTexture, nullptr, &dst );
}