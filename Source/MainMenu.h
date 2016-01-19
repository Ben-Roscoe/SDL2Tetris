#pragma once

#include <SDL.h>
#include <SDL_ttf.h>


enum class MainMenuOption
{
	Play,
	Quit,
};

struct MainMenu
{
	SDL_Texture*	playOptionTexture	= nullptr;
	SDL_Point		playOptionSize;

	SDL_Texture*	quitOptionTexture	= nullptr;
	SDL_Point		quitOptionSize;

	MainMenuOption	highlightedOption	= MainMenuOption::Play;
};


void MainMenu_New( MainMenu& mainMenu, SDL_Renderer* renderer, TTF_Font* font );
void MainMenu_Destroy( MainMenu& mainMenu );
void MainMenu_SetHighlighted( MainMenu& mainMenu, MainMenuOption option );
void MainMenu_Draw( MainMenu& mainMenu, SDL_Renderer* renderer, const SDL_Rect& origin );