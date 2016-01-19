#include "Level.h"
#include "Utility.h"
#include <stdio.h>

const SDL_Color	LevelTextColour = { 0xFF, 0xFF, 0xFF }; 
const char*		LevelTitleText  = "Level";


void Level_New( Level& level, SDL_Renderer* renderer, TTF_Font* font )
{
	Utility_BuildFontTexture( &level.titleTexture, &level.titleTextureSize, LevelTitleText, LevelTextColour, renderer, font );

	char buffer[30];
	sprintf_s( buffer, "%d", level.value );
	Utility_BuildFontTexture( &level.levelTexture, &level.levelTextureSize, buffer, LevelTextColour, renderer, font );
}


void Level_Destroy( Level& level )
{
	if( level.titleTexture != nullptr )
	{
		SDL_DestroyTexture( level.titleTexture );
	}
	if( level.levelTexture != nullptr )
	{
		SDL_DestroyTexture( level.levelTexture );
	}
}


void Level_SetLevel( Level& level, int value )
{
	level.value				= value;

	if( level.value != 0 )
	{
		level.speedMultiplier = 1.0f / ( level.value * 0.95f );
	}
	else
	{
		level.speedMultiplier = 1.0f;
	}
}


void Level_Draw( Level& level, SDL_Renderer* renderer, const SDL_Point& origin, TTF_Font* font )
{
	if( level.oldValue != level.value )
	{
		level.oldValue = level.value;

		// Rebuild font texture.
		char buffer[30];
		sprintf_s( buffer, "%d", level.value );
		Utility_BuildFontTexture( &level.levelTexture, &level.levelTextureSize, buffer, LevelTextColour, renderer, font );
	}

	SDL_Rect dst;
	dst.x = origin.x - level.titleTextureSize.x / 2.0f;
	dst.y = origin.y - level.titleTextureSize.y / 2.0f;
	dst.w = level.titleTextureSize.x;
	dst.h = level.titleTextureSize.y;
	SDL_RenderCopy( renderer, level.titleTexture, nullptr, &dst );

	dst.x = origin.x - level.levelTextureSize.x / 2.0f;
	dst.y = origin.y + level.titleTextureSize.y - level.levelTextureSize.y / 2.0f;
	dst.w = level.levelTextureSize.x;
	dst.h = level.levelTextureSize.y;
	SDL_RenderCopy( renderer, level.levelTexture, nullptr, &dst );
}