#pragma once

#include <SDL.h>
#include <SDL_ttf.h>


enum class PauseMenuOption
{
	Continue,
	Quit,
};


struct PauseMenu
{
	SDL_Texture*	continueOptionTexture;
	SDL_Point		continueOptionSize;

	SDL_Texture*	quitOptionTexture;
	SDL_Point		quitOptionSize;

	PauseMenuOption	highlightedOption	= PauseMenuOption::Continue;
};


void PauseMenu_New( PauseMenu& pauseMenu, SDL_Renderer* renderer, TTF_Font* font );
void PauseMenu_Destroy( PauseMenu& pauseMenu );
void PauseMenu_SetHighlighted( PauseMenu& pauseMenu, PauseMenuOption option );
void PauseMenu_Draw( PauseMenu& pauseMenu, SDL_Renderer* renderer, const SDL_Point& origin );