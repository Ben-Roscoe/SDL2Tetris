#include "GameOverDisplay.h"


const char*		GameOverText			  = "Game Over";
const char*		GameOverContinueText      = "Press Space to continue";
const char*		GameOverHighScoreText     = "You got a high score!";
const SDL_Color GameOverDisplayTextColour = { 0xFF, 0xFF, 0xFF };


static void GameOverDislay_BuildGameOverTexture( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, TTF_Font* font )
{
	// Build score texture.
	if( gameOverDisplay.gameOverTexture != nullptr )
	{
		SDL_DestroyTexture( gameOverDisplay.gameOverTexture );
		gameOverDisplay.gameOverTexture = nullptr;
	}

	// Rebuild from font.
	auto surface					= TTF_RenderText_Solid( font, GameOverText, GameOverDisplayTextColour );
	gameOverDisplay.gameOverTexture	= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	SDL_QueryTexture( gameOverDisplay.gameOverTexture, nullptr, nullptr,
					  &gameOverDisplay.gameOverTextureSize.x, &gameOverDisplay.gameOverTextureSize.y );
}


static void GameOverDisplay_BuildContinueTexture( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, TTF_Font* font )
{
	// Build score texture.
	if( gameOverDisplay.continueTexture != nullptr )
	{
		SDL_DestroyTexture( gameOverDisplay.continueTexture );
		gameOverDisplay.continueTexture = nullptr;
	}

	// Rebuild from font.
	auto surface					= TTF_RenderText_Solid( font, GameOverContinueText, GameOverDisplayTextColour );
	gameOverDisplay.continueTexture	= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	SDL_QueryTexture( gameOverDisplay.continueTexture, nullptr, nullptr,
						  &gameOverDisplay.continueTextureSize.x, &gameOverDisplay.continueTextureSize.y );
}


static void GameOverDisplay_BuildHighScoreTexture( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, TTF_Font* font )
{
	// Build score texture.
	if( gameOverDisplay.highScoreTexture != nullptr )
	{
		SDL_DestroyTexture( gameOverDisplay.highScoreTexture );
		gameOverDisplay.highScoreTexture = nullptr;
	}

	// Rebuild from font.
	auto surface						= TTF_RenderText_Solid( font, GameOverHighScoreText, GameOverDisplayTextColour );
	gameOverDisplay.highScoreTexture	= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	SDL_QueryTexture( gameOverDisplay.highScoreTexture, nullptr, nullptr,
						  &gameOverDisplay.hightScoreTextureSize.x, &gameOverDisplay.hightScoreTextureSize.y );
}


void GameOverDisplay_New( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, TTF_Font* font, const char* scoreBoardFileName )
{
	GameOverDislay_BuildGameOverTexture( gameOverDisplay, renderer, font );
	GameOverDisplay_BuildContinueTexture( gameOverDisplay, renderer, font );
	GameOverDisplay_BuildHighScoreTexture( gameOverDisplay, renderer, font );

	ScoreBoard_Load( gameOverDisplay.scoreBoard, scoreBoardFileName, renderer, font );
}


void GameOverDisplay_Destroy( GameOverDisplay& gameOverDisplay, const char* scoreBoardFileName )
{
	// Save and destroy the score board.
	ScoreBoard_Save( gameOverDisplay.scoreBoard, scoreBoardFileName );
	ScoreBoard_Destroy( gameOverDisplay.scoreBoard );
	
	// Destroy our textures.
	if( gameOverDisplay.gameOverTexture != nullptr )
	{
		SDL_DestroyTexture( gameOverDisplay.gameOverTexture );
		gameOverDisplay.gameOverTexture = nullptr;
	}
	if( gameOverDisplay.continueTexture != nullptr )
	{
		SDL_DestroyTexture( gameOverDisplay.continueTexture );
		gameOverDisplay.continueTexture = nullptr;
	}
}


void GameOverDisplay_Draw( GameOverDisplay& gameOverDisplay, SDL_Renderer* renderer, const SDL_Point& origin )
{
	SDL_Rect dst;
	dst.x = origin.x - ( gameOverDisplay.gameOverTextureSize.x / 2.0f );
	dst.y = origin.y - ( gameOverDisplay.gameOverTextureSize.y / 2.0f );
	dst.w = gameOverDisplay.gameOverTextureSize.x;
	dst.h = gameOverDisplay.gameOverTextureSize.y;
	SDL_RenderCopy( renderer, gameOverDisplay.gameOverTexture, nullptr, &dst );

	dst.y += gameOverDisplay.gameOverTextureSize.y;
	if( gameOverDisplay.isHighScorer )
	{
		dst.w = gameOverDisplay.hightScoreTextureSize.x;
		dst.h = gameOverDisplay.hightScoreTextureSize.y;
		dst.x = origin.x - dst.w / 2.0f;
		SDL_RenderCopy( renderer, gameOverDisplay.highScoreTexture, nullptr, &dst );
	}

	dst.y += gameOverDisplay.gameOverTextureSize.y * 3;
	SDL_Point scoreBoardOrigin;
	scoreBoardOrigin.x = origin.x;
	scoreBoardOrigin.y = dst.y;
	
	int scoreBoardBottom = ScoreBoard_Draw( gameOverDisplay.scoreBoard, renderer, scoreBoardOrigin );
	scoreBoardBottom += gameOverDisplay.continueTextureSize.y;

	dst.x = origin.x - ( gameOverDisplay.continueTextureSize.x / 2.0f );
	dst.y = scoreBoardBottom - ( gameOverDisplay.continueTextureSize.y / 2.0f );
	dst.w = gameOverDisplay.continueTextureSize.x;
	dst.h = gameOverDisplay.continueTextureSize.y;
	SDL_RenderCopy( renderer, gameOverDisplay.continueTexture, nullptr, &dst );
}