#pragma once
#include <SDL.h>
#include <SDL_ttf.h>


void Utility_BuildFontTexture( SDL_Texture** outTexture, SDL_Point* outSize, const char* text,
							   const SDL_Color& colour, SDL_Renderer* renderer, TTF_Font* font );