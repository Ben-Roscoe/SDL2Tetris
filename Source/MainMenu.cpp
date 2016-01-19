#include "MainMenu.h"
#include "Utility.h"
#include <iostream>

const SDL_Color MainMenuOptionsUnselectedColour = { 0xFF, 0xFF, 0xFF };
const SDL_Color	MainMenuOptionsSelectedColour	= { 0xFF, 0xFB, 0x30 };

const char* PlayOptionText = "Play";
const char* QuitOptionText = "Quit";


void MainMenu_New( MainMenu& mainMenu, SDL_Renderer* renderer, TTF_Font* font )
{
	mainMenu.playOptionTexture	= nullptr;
	mainMenu.quitOptionTexture	= nullptr;

	Utility_BuildFontTexture( &mainMenu.playOptionTexture, &mainMenu.playOptionSize, 
								PlayOptionText, MainMenuOptionsUnselectedColour, renderer, font );
	Utility_BuildFontTexture( &mainMenu.quitOptionTexture, &mainMenu.quitOptionSize, 
								QuitOptionText, MainMenuOptionsUnselectedColour, renderer, font );

	MainMenu_SetHighlighted( mainMenu, MainMenuOption::Play );
}


void MainMenu_Destroy( MainMenu& mainMenu )
{
	if( mainMenu.playOptionTexture != nullptr )
	{
		SDL_DestroyTexture( mainMenu.playOptionTexture );
	}
	if( mainMenu.quitOptionTexture != nullptr )
	{
		SDL_DestroyTexture( mainMenu.quitOptionTexture );
	}
}


void MainMenu_SetHighlighted( MainMenu& mainMenu, MainMenuOption option )
{
	mainMenu.highlightedOption = option;
	if( SDL_SetTextureColorMod( mainMenu.highlightedOption == MainMenuOption::Play ?
							mainMenu.playOptionTexture : mainMenu.quitOptionTexture,
							MainMenuOptionsSelectedColour.r, MainMenuOptionsSelectedColour.g,
							MainMenuOptionsSelectedColour.b ) != 0 )
	{
		std::cout << "SDL_SetTextureColorMod MainMenu Error: " << SDL_GetError() << std::endl;
	}
	if( SDL_SetTextureColorMod( mainMenu.highlightedOption != MainMenuOption::Play ? 
							mainMenu.playOptionTexture : mainMenu.quitOptionTexture,
							MainMenuOptionsUnselectedColour.r, MainMenuOptionsUnselectedColour.g,
							MainMenuOptionsUnselectedColour.b ) != 0 )
	{
		std::cout << "SDL_SetTextureColorMod MainMenu Error: " << SDL_GetError() << std::endl;
	}
}


void MainMenu_Draw( MainMenu& mainMenu, SDL_Renderer* renderer, const SDL_Rect& origin )
{
	SDL_Rect dst;
	dst.w = mainMenu.playOptionSize.x;
	dst.h = mainMenu.playOptionSize.y;
	dst.x = origin.x;
	dst.y = origin.y;
	SDL_RenderCopy( renderer, mainMenu.playOptionTexture, nullptr, &dst );

	dst.w = mainMenu.quitOptionSize.x;
	dst.h = mainMenu.quitOptionSize.y;
	dst.y += mainMenu.playOptionSize.y;
	SDL_RenderCopy( renderer, mainMenu.quitOptionTexture, nullptr, &dst );
}