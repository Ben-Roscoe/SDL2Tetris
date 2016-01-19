#include "Utility.h"


void Utility_BuildFontTexture( SDL_Texture** outTexture, SDL_Point* outSize, const char* text, const SDL_Color& colour, SDL_Renderer* renderer, TTF_Font* font )
{
	// Build score texture.
	if( *outTexture != nullptr )
	{
		SDL_DestroyTexture( *outTexture );
		*outTexture = nullptr;
	}

	// Rebuild from font.
	auto surface					= TTF_RenderText_Solid( font, text, colour );
	*outTexture						= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	SDL_QueryTexture( *outTexture, nullptr, nullptr,
					  &outSize->x, &outSize->y );
}