#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

struct Score
{
	// Store old value so we can change the texture only
	// when the score changes.
	int			value			= 0;
	int			oldValue		= -1;
	SDL_Texture* scoreTexture	= nullptr;
	SDL_Texture* titleTexture	= nullptr;

	// Cache some data on the textures to help with drawing.
	SDL_Point	titleSize;
	SDL_Point	scoreSize;
};


void Score_New( Score& score, SDL_Renderer* renderer, TTF_Font* titleFont );
void Score_Destroy( Score& score );
void Score_Add( Score& score, int delta );
void Score_Clear( Score& score );
void Score_Draw( Score& score, SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& origin );