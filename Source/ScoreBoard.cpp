#include "ScoreBoard.h"
#include <stdio.h>
#include <iostream>
#include <string.h>


const SDL_Color ScoreBoardTextColour = { 0xFF, 0xFF, 0xFF };
const char*		ScoreBoardHeaderText = "Highscores";


void ScoreBoardEntry_New( ScoreBoardEntry& scoreBoardEntry, int score, int position, SDL_Renderer* renderer, TTF_Font* font )
{
	ScoreBoardEntry_SetScorePosition( scoreBoardEntry, score, position, renderer, font );
}


void ScoreBoardEntry_SetScorePosition( ScoreBoardEntry& scoreBoardEntry, int score, int position, SDL_Renderer* renderer, TTF_Font* font )
{
	scoreBoardEntry.score = score;
	
	// Build score texture.
	if( scoreBoardEntry.texture != nullptr )
	{
		SDL_DestroyTexture( scoreBoardEntry.texture );
		scoreBoardEntry.texture = nullptr;
	}

	// Get score string.
	char buffer[30];
	sprintf_s( buffer, " %d. %d", position, scoreBoardEntry.score );

	// Rebuild from font.
	auto surface			= TTF_RenderText_Solid( font, buffer, ScoreBoardTextColour );
	scoreBoardEntry.texture	= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	TTF_SizeText( font, buffer, &scoreBoardEntry.size.x, &scoreBoardEntry.size.y );
}


void ScoreBoardEntry_Destroy( ScoreBoardEntry& scoreBoardEntry )
{
	if( scoreBoardEntry.texture != nullptr )
	{
		SDL_DestroyTexture( scoreBoardEntry.texture );
	}
}


static void ScoreBoard_BuildTexture( ScoreBoard& scoreBoard, SDL_Renderer* renderer, TTF_Font* font )
{
	// Build score texture.
	if( scoreBoard.texture != nullptr )
	{
		SDL_DestroyTexture( scoreBoard.texture );
		scoreBoard.texture = nullptr;
	}

	// Rebuild from font.
	auto surface		= TTF_RenderText_Solid( font, ScoreBoardHeaderText, ScoreBoardTextColour );
	scoreBoard.texture	= SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );

	TTF_SizeText( font, ScoreBoardHeaderText, &scoreBoard.textureSize.x, &scoreBoard.textureSize.y );
}


static void ScoreBoard_New( ScoreBoard& scoreBoard, SDL_Renderer* renderer, TTF_Font* font )
{
	for( int i = 0; i < MaxHighScores; ++i )
	{
		ScoreBoardEntry_New( scoreBoard.highScores[i], 0, i + 1, renderer, font );
	}
}


void ScoreBoard_Load( ScoreBoard& scoreBoard, const char* fileName, SDL_Renderer* renderer, TTF_Font* font )
{
	FILE* file;
	fopen_s( &file, fileName, "r+t" );
	if( file == nullptr )
	{
		std::cout << "No score board file to load. Creating new score board." << std::endl;
		ScoreBoard_New( scoreBoard, renderer, font );
		return;
	}

	char buffer[512];
	std::memset( buffer, 0, sizeof( buffer ) );
	int  n = fread_s( buffer, sizeof( buffer ), sizeof( char ), sizeof( buffer ), file );
	
	// Convert all ',''s to '\0''s.
	for( int c = 0; c < n; ++c )
	{
		if( buffer[c] == ',' )
		{
			buffer[c] = '\0';
		}
	}

	// Read each score.
	int i = 0;
	int s = 0;
	while( i < n )
	{
		ScoreBoardEntry_New( scoreBoard.highScores[s], strtol( &buffer[i], nullptr, 10 ), s + 1, renderer, font );
		i += strlen( &buffer[i] ) + 1;
		++s;
	}

	fclose( file );
}


void ScoreBoard_Save( const ScoreBoard& scoreBoard, const char* fileName )
{
	FILE* file;
	fopen_s( &file, fileName, "w" );
	if( file == nullptr )
	{
		std::cout << "Score board error: " << "Could not open file for writing: " << fileName << std::endl;
		return;
	}

	for( int i = 0; i < MaxHighScores; ++i )
	{
		fprintf_s( file, "%d,", scoreBoard.highScores[i].score );
	}

	fclose( file );
}


bool ScoreBoard_Submit( ScoreBoard& scoreBoard, int score, SDL_Renderer* renderer, TTF_Font* font )
{
	// Return false if no high score was achieved, return true and
	// insert the score if it was a highscore.
	for( int i = 0; i < MaxHighScores; ++i )
	{
		if( scoreBoard.highScores[i].score <= score )
		{
			for( int s = MaxHighScores - 1; s > i; --s )
			{
				ScoreBoardEntry_SetScorePosition( scoreBoard.highScores[s], scoreBoard.highScores[s - 1].score, s + 1, renderer, font );
			}
			scoreBoard.highScores[i].texture = nullptr;
			ScoreBoardEntry_SetScorePosition( scoreBoard.highScores[i], score, i + 1, renderer, font );
			return true;
		}
	}
	return false;
}


void ScoreBoard_Destroy( ScoreBoard& scoreBoard )
{
	for( int i = 0; i < MaxHighScores; ++i )
	{
		ScoreBoardEntry_Destroy( scoreBoard.highScores[i] );
	}
	if( scoreBoard.texture != nullptr )
	{
		SDL_DestroyTexture( scoreBoard.texture );
		scoreBoard.texture = nullptr;
	}
}


int ScoreBoard_Draw( ScoreBoard& scoreBoard, SDL_Renderer* renderer, const SDL_Point& origin )
{
	SDL_Rect dst;
	dst.x = origin.x;
	dst.y = origin.y;
	dst.w = scoreBoard.textureSize.x;
	dst.h = scoreBoard.textureSize.y;
	SDL_RenderCopy( renderer, scoreBoard.texture, nullptr, &dst );

	float scoresHeight = dst.y + scoreBoard.textureSize.y * 2;
	for( int i = 0; i < MaxHighScores; ++i )
	{
		dst.x = origin.x - ( scoreBoard.highScores[i].size.x / 2.0f );
		dst.y = scoresHeight;
		dst.w = scoreBoard.highScores[i].size.x;
		dst.h = scoreBoard.highScores[i].size.y;
		SDL_RenderCopy( renderer, scoreBoard.highScores[i].texture, nullptr, &dst );
		scoresHeight += scoreBoard.highScores[i].size.y;
	}

	return scoresHeight;
}