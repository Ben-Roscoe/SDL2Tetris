#include "PauseMenu.h"
#include "Utility.h"
#include <iostream>

static const SDL_Color PauseMenuUnhighlightedTextColour		= { 0xFF, 0xFF, 0xFF };
static const SDL_Color PauseMenuHighlightedTextColour		= { 0xFF, 0xFB, 0x30 };

static const char* PauseMenuContinueOptionText  = "Continue";
static const char* PauseMenuQuitOptionText		= "Quit";


void PauseMenu_New( PauseMenu& pauseMenu, SDL_Renderer* renderer, TTF_Font* font )
{
	Utility_BuildFontTexture( &pauseMenu.continueOptionTexture, &pauseMenu.continueOptionSize, PauseMenuContinueOptionText,
								PauseMenuUnhighlightedTextColour, renderer, font );
	Utility_BuildFontTexture( &pauseMenu.quitOptionTexture, &pauseMenu.quitOptionSize, PauseMenuQuitOptionText,
								PauseMenuUnhighlightedTextColour, renderer, font );
}


void PauseMenu_Destroy( PauseMenu& pauseMenu )
{
	if( pauseMenu.continueOptionTexture != nullptr )
	{
		SDL_DestroyTexture( pauseMenu.continueOptionTexture );
		pauseMenu.continueOptionTexture = nullptr;
	}
	if( pauseMenu.quitOptionTexture != nullptr )
	{
		SDL_DestroyTexture( pauseMenu.quitOptionTexture );
		pauseMenu.quitOptionTexture = nullptr;
	}
}


void PauseMenu_SetHighlighted( PauseMenu& pauseMenu, PauseMenuOption option )
{
	pauseMenu.highlightedOption = option;
	if( SDL_SetTextureColorMod( pauseMenu.highlightedOption == PauseMenuOption::Continue ?
							pauseMenu.continueOptionTexture : pauseMenu.quitOptionTexture,
							PauseMenuHighlightedTextColour.r, PauseMenuHighlightedTextColour.g,
							PauseMenuHighlightedTextColour.b ) != 0 )
	{
		std::cout << "SDL_SetTextureColorMod MainMenu Error: " << SDL_GetError() << std::endl;
	}
	if( SDL_SetTextureColorMod( pauseMenu.highlightedOption != PauseMenuOption::Quit ? 
							pauseMenu.quitOptionTexture : pauseMenu.continueOptionTexture,
							PauseMenuUnhighlightedTextColour.r, PauseMenuUnhighlightedTextColour.g,
							PauseMenuUnhighlightedTextColour.b ) != 0 )
	{
		std::cout << "SDL_SetTextureColorMod MainMenu Error: " << SDL_GetError() << std::endl;
	}
}


void PauseMenu_Draw( PauseMenu& pauseMenu, SDL_Renderer* renderer, const SDL_Point& origin )
{
	SDL_Rect dst;
	dst.w = pauseMenu.continueOptionSize.x;
	dst.h = pauseMenu.continueOptionSize.y;
	dst.x = origin.x - pauseMenu.continueOptionSize.x / 2.0f;
	dst.y = origin.y - pauseMenu.continueOptionSize.y / 2.0f;
	SDL_RenderCopy( renderer, pauseMenu.continueOptionTexture, nullptr, &dst );

	dst.w = pauseMenu.quitOptionSize.x;
	dst.h = pauseMenu.quitOptionSize.y;
	dst.x = origin.x - pauseMenu.quitOptionSize.x / 2.0f;
	dst.y += pauseMenu.continueOptionSize.y;
	SDL_RenderCopy( renderer, pauseMenu.quitOptionTexture, nullptr, &dst );
}