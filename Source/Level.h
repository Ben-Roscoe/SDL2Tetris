#pragma once
#include <SDL.h>
#include <SDL_ttf.h>


struct Level
{
	int		value				= 0;
	int		oldValue			= 0;
	float	speedMultiplier		= 1.0f;

	SDL_Texture*	titleTexture		= nullptr;
	SDL_Point		titleTextureSize;

	SDL_Texture*	levelTexture		= nullptr;
	SDL_Point		levelTextureSize;
};


void Level_New( Level& level, SDL_Renderer* renderer, TTF_Font* font );
void Level_Destroy( Level& level );
void Level_SetLevel( Level& level, int value );
void Level_Draw( Level& level, SDL_Renderer* renderer, const SDL_Point& origin, TTF_Font* font );