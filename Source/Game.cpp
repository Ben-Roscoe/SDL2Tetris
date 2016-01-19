#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include <random>


const char* ScoreBoardFileName = "ScoreBoard.txt";

static void Game_StartPlaying( Game& game );
static void Game_EndPlaying( Game& game );
static void Game_StartMainMenu( Game& game );
static void Game_EndMainMenu( Game& game );
static void Game_EndMainMenu( Game& game );
static void Game_StartPause( Game& game );
static void Game_EndPause( Game& game );
static void Game_StartGameOver( Game& game );
static void Game_EndGameOver( Game& game );


static void Game_ConstructTetrisPieces( Game& game )
{
	// Right L-block.
	game.pieceBlocks[0].space = 3;

	game.pieceBlocks[0].blocks[0][0].active = false;
	game.pieceBlocks[0].blocks[0][1].active = true;
	game.pieceBlocks[0].blocks[0][2].active = false;
	game.pieceBlocks[0].blocks[0][3].active = false;

	game.pieceBlocks[0].blocks[1][0].active = false;
	game.pieceBlocks[0].blocks[1][1].active = true;
	game.pieceBlocks[0].blocks[1][2].active = false;
	game.pieceBlocks[0].blocks[1][3].active = false;

	game.pieceBlocks[0].blocks[2][0].active = true;
	game.pieceBlocks[0].blocks[2][1].active = true;
	game.pieceBlocks[0].blocks[2][2].active = false;
	game.pieceBlocks[0].blocks[2][3].active = false;

	game.pieceBlocks[0].blocks[3][0].active = false;
	game.pieceBlocks[0].blocks[3][1].active = false;
	game.pieceBlocks[0].blocks[3][2].active = false;
	game.pieceBlocks[0].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[0], 0x00FF0000 );


	// T-block.
	game.pieceBlocks[1].space = 3;

	game.pieceBlocks[1].blocks[0][0].active = false;
	game.pieceBlocks[1].blocks[0][1].active = true;
	game.pieceBlocks[1].blocks[0][2].active = false;
	game.pieceBlocks[1].blocks[0][3].active = false;

	game.pieceBlocks[1].blocks[1][0].active = true;
	game.pieceBlocks[1].blocks[1][1].active = true;
	game.pieceBlocks[1].blocks[1][2].active = false;
	game.pieceBlocks[1].blocks[1][3].active = false;

	game.pieceBlocks[1].blocks[2][0].active = false;
	game.pieceBlocks[1].blocks[2][1].active = true;
	game.pieceBlocks[1].blocks[2][2].active = false;
	game.pieceBlocks[1].blocks[2][3].active = false;

	game.pieceBlocks[1].blocks[3][0].active = false;
	game.pieceBlocks[1].blocks[3][1].active = false;
	game.pieceBlocks[1].blocks[3][2].active = false;
	game.pieceBlocks[1].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[1], 0x00FFDB00 );

	// Left L-block.
	game.pieceBlocks[2].space = 3;

	game.pieceBlocks[2].blocks[0][0].active = true;
	game.pieceBlocks[2].blocks[0][1].active = true;
	game.pieceBlocks[2].blocks[0][2].active = false;
	game.pieceBlocks[2].blocks[0][3].active = false;

	game.pieceBlocks[2].blocks[1][0].active = false;
	game.pieceBlocks[2].blocks[1][1].active = true;
	game.pieceBlocks[2].blocks[1][2].active = false;
	game.pieceBlocks[2].blocks[1][3].active = false;

	game.pieceBlocks[2].blocks[2][0].active = false;
	game.pieceBlocks[2].blocks[2][1].active = true;
	game.pieceBlocks[2].blocks[2][2].active = false;
	game.pieceBlocks[2].blocks[2][3].active = false;

	game.pieceBlocks[2].blocks[3][0].active = false;
	game.pieceBlocks[2].blocks[3][1].active = false;
	game.pieceBlocks[2].blocks[3][2].active = false;
	game.pieceBlocks[2].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[2], 0x0049FF00 );

	// Left S-block.
	game.pieceBlocks[3].space = 3;

	game.pieceBlocks[3].blocks[0][0].active = false;
	game.pieceBlocks[3].blocks[0][1].active = false;
	game.pieceBlocks[3].blocks[0][2].active = true;
	game.pieceBlocks[3].blocks[0][3].active = false;

	game.pieceBlocks[3].blocks[1][0].active = false;
	game.pieceBlocks[3].blocks[1][1].active = true;
	game.pieceBlocks[3].blocks[1][2].active = true;
	game.pieceBlocks[3].blocks[1][3].active = false;

	game.pieceBlocks[3].blocks[2][0].active = false;
	game.pieceBlocks[3].blocks[2][1].active = true;
	game.pieceBlocks[3].blocks[2][2].active = false;
	game.pieceBlocks[3].blocks[2][3].active = false;

	game.pieceBlocks[3].blocks[3][0].active = false;
	game.pieceBlocks[3].blocks[3][1].active = false;
	game.pieceBlocks[3].blocks[3][2].active = false;
	game.pieceBlocks[3].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[3], 0x0000FF92 );

	// Straight block.
	game.pieceBlocks[4].space = 4;

	game.pieceBlocks[4].blocks[0][0].active = false;
	game.pieceBlocks[4].blocks[0][1].active = false;
	game.pieceBlocks[4].blocks[0][2].active = true;
	game.pieceBlocks[4].blocks[0][3].active = false;

	game.pieceBlocks[4].blocks[1][0].active = false;
	game.pieceBlocks[4].blocks[1][1].active = false;
	game.pieceBlocks[4].blocks[1][2].active = true;
	game.pieceBlocks[4].blocks[1][3].active = false;

	game.pieceBlocks[4].blocks[2][0].active = false;
	game.pieceBlocks[4].blocks[2][1].active = false;
	game.pieceBlocks[4].blocks[2][2].active = true;
	game.pieceBlocks[4].blocks[2][3].active = false;

	game.pieceBlocks[4].blocks[3][0].active = false;
	game.pieceBlocks[4].blocks[3][1].active = false;
	game.pieceBlocks[4].blocks[3][2].active = true;
	game.pieceBlocks[4].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[4], 0x000092FF );


	// Square block.
	game.pieceBlocks[5].space = 2;

	game.pieceBlocks[5].blocks[0][0].active = true;
	game.pieceBlocks[5].blocks[0][1].active = true;
	game.pieceBlocks[5].blocks[0][2].active = false;
	game.pieceBlocks[5].blocks[0][3].active = false;

	game.pieceBlocks[5].blocks[1][0].active = true;
	game.pieceBlocks[5].blocks[1][1].active = true;
	game.pieceBlocks[5].blocks[1][2].active = false;
	game.pieceBlocks[5].blocks[1][3].active = false;

	game.pieceBlocks[5].blocks[2][0].active = false;
	game.pieceBlocks[5].blocks[2][1].active = false;
	game.pieceBlocks[5].blocks[2][2].active = false;
	game.pieceBlocks[5].blocks[2][3].active = false;

	game.pieceBlocks[5].blocks[3][0].active = false;
	game.pieceBlocks[5].blocks[3][1].active = false;
	game.pieceBlocks[5].blocks[3][2].active = false;
	game.pieceBlocks[5].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[5], 0x004900FF );


	// Right S-Block.
	game.pieceBlocks[6].space = 3;

	game.pieceBlocks[6].blocks[0][0].active = true;
	game.pieceBlocks[6].blocks[0][1].active = false;
	game.pieceBlocks[6].blocks[0][2].active = false;
	game.pieceBlocks[6].blocks[0][3].active = false;

	game.pieceBlocks[6].blocks[1][0].active = true;
	game.pieceBlocks[6].blocks[1][1].active = true;
	game.pieceBlocks[6].blocks[1][2].active = false;
	game.pieceBlocks[6].blocks[1][3].active = false;

	game.pieceBlocks[6].blocks[2][0].active = false;
	game.pieceBlocks[6].blocks[2][1].active = true;
	game.pieceBlocks[6].blocks[2][2].active = false;
	game.pieceBlocks[6].blocks[2][3].active = false;

	game.pieceBlocks[6].blocks[3][0].active = false;
	game.pieceBlocks[6].blocks[3][1].active = false;
	game.pieceBlocks[6].blocks[3][2].active = false;
	game.pieceBlocks[6].blocks[3][3].active = false;

	PieceFormation_SetColour( game.pieceBlocks[6], 0x00FF00DB );
}


static void Game_RefreshRandomPiecePool( Game& game )
{
	for( int i = 0; i < TotalTetrisPieces; ++i )
	{
		// Line piece spawns every second refresh OR with random %50 chance.
		if( i == 4 && !game.spawnLinePiece && std::rand() % 2 == 0 )
		{
			continue;
		}
		game.randomPiecePool[i] = &game.pieceBlocks[i];
		++game.randomPiecesLeft;
	}

	game.spawnLinePiece = !game.spawnLinePiece;
}


static PieceFormation* Game_GetRandomPiece( Game& game )
{
	// Refresh the pool if we're out of pieces.
	if( game.randomPiecesLeft <= 0 )
	{
		Game_RefreshRandomPiecePool( game );
	}

	// Get the initial index. If this is nullptr, decrement the 
	// index and wrap around until we get a valid piece.
	auto index = std::rand() % game.randomPiecesLeft;

	PieceFormation* piece = game.randomPiecePool[index];
	while( piece == nullptr )
	{
		--index;
		if( index < 0 )
		{
			index = TotalTetrisPieces - 1;
		}
		piece = game.randomPiecePool[index];
	} 
	
	game.randomPiecePool[index] = nullptr;
	--game.randomPiecesLeft;
	return piece;
}


static PieceFormation* Game_PushBackQueue( Game& game )
{
	auto piece = Game_GetRandomPiece( game );
	return PieceQueue_PushBack( game.pieceQueue, piece );
}


static void Game_FillQueue( Game& game )
{
	for( int i = 0; i < PieceQueueSize; ++i )
	{
		Game_PushBackQueue( game );
	}
}


static void Game_StartMainMenu( Game& game )
{
	game.gameState = GameState::MainMenu;
	MainMenu_SetHighlighted( game.mainMenu, MainMenuOption::Play );
}


static void Game_EndMainMenu( Game& game )
{
	Game_StartPlaying( game );
}


static void Game_StartPlaying( Game& game )
{
	game.gameState = GameState::Playing;
	game.randomPiecesLeft = 0;
	Game_RefreshRandomPiecePool( game );
	Game_FillQueue( game );
	Score_Clear( game.score );
	Board_Reset( game.board );
	Level_SetLevel( game.level, 0 );
}


static void Game_EndPlaying( Game& game )
{
	Hold_Clear( game.hold );
	PieceQueue_Clear( game.pieceQueue );
	Game_StartGameOver( game );
}


static void Game_StartPause( Game& game )
{
	game.gameState = GameState::Paused;
	PauseMenu_SetHighlighted( game.pauseMenu, PauseMenuOption::Continue );
}


static void Game_EndPause( Game& game )
{
	game.gameState = GameState::Playing;
}


static void Game_StartGameOver( Game& game )
{
	game.gameState = GameState::GameOver;
}


static void Game_EndGameOver( Game& game )
{
	Game_StartMainMenu( game );
}


static void Game_ProcessInput( Game& game )
{
	if( game.gameState == GameState::Playing )
	{
		if( game.userCmd.states[static_cast<size_t>( Cmds::Pause )].pressedThisFrame )
		{
			Game_StartPause( game );
		}
		else
		{
			auto fallingPiece = Board_GetFirstFallingPiece( game.board );
			if( fallingPiece != nullptr )
			{
				std::srand( SDL_GetTicks() );
				if( game.userCmd.states[static_cast<size_t>( Cmds::Hold )].pressedThisFrame
					&& Hold_CanHold( game.hold ) )
				{
					Mix_PlayChannel( -1, game.pieceHoldSound, 0 );

					Board_RemovePiece( game.board, *fallingPiece );
					Board_DestroyPiece( game.board, *fallingPiece, &game.score, &game.level,
										game.clearSingleDoubleSound, game.clearTripleSound,
										game.clearTetrisSound );

					auto held = Hold_HoldFormation( game.hold, game.currentFormation );
					if( held != nullptr )
					{
						Board_NewPiece( game.board, *held );
					}
				}
				else
				{
					if( game.userCmd.states[static_cast<size_t>( Cmds::MoveLeft )].activated )
					{
						Board_AdjustPiecePosition( game.board, *fallingPiece, -1, 0 );
					}
					if( game.userCmd.states[static_cast<size_t>( Cmds::MoveRight )].activated )
					{
						Board_AdjustPiecePosition( game.board, *fallingPiece, 1, 0 );
					}
					if( game.userCmd.states[static_cast<size_t>( Cmds::FallFaster )].activated )
					{
						Board_AdjustPiecePosition( game.board, *fallingPiece, 0, 1 );
					}
					if( game.userCmd.states[static_cast<size_t>( Cmds::RotateRight )].pressedThisFrame )
					{
						Mix_PlayChannel( -1, game.pieceRotateSound, 0 );
						Board_RotatePiece( game.board, *fallingPiece, PieceRotation::Right );
					}
					if( game.userCmd.states[static_cast<size_t>( Cmds::Drop )].activated )
					{
						Mix_PlayChannel( -1, game.pieceHardDropSound, 0 );

						// Drop the piece and remove it from the active list.
						Board_RemovePiece( game.board, *fallingPiece );
						Board_DropPiece( game.board, *fallingPiece );
						Board_AddPiece( game.board, *fallingPiece );
						Board_DestroyPiece( game.board, *fallingPiece, &game.score, &game.level,
											game.clearSingleDoubleSound, game.clearTripleSound,
											game.clearTetrisSound );

						Hold_ResetHold( game.hold );
					}
				}
			}
		}
	}
	else if( game.gameState == GameState::MainMenu )
	{
		if( game.userCmd.states[static_cast<size_t>( Cmds::RotateRight )].pressedThisFrame
			|| game.userCmd.states[static_cast<size_t>( Cmds::FallFaster )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuHighlightChanegSound, 0 );
			MainMenu_SetHighlighted( game.mainMenu,
									 game.mainMenu.highlightedOption == MainMenuOption::Play ? 
									 MainMenuOption::Quit : MainMenuOption::Play );
		}
		if( game.userCmd.states[static_cast<size_t>( Cmds::Confirm )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuSelectedSound, 0 );
			if( game.mainMenu.highlightedOption == MainMenuOption::Quit )
			{
				game.quit = true;
			}
			else
			{
				Game_EndMainMenu( game );
			}
		}
	}
	else if( game.gameState == GameState::Paused )
	{
		if( game.userCmd.states[static_cast<size_t>( Cmds::Pause )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuSelectedSound, 0 );
			Game_EndPause( game );
		}
		else if( game.userCmd.states[static_cast<size_t>( Cmds::RotateRight )].pressedThisFrame
				|| game.userCmd.states[static_cast<size_t>( Cmds::FallFaster )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuHighlightChanegSound, 0 );
			PauseMenu_SetHighlighted( game.pauseMenu,
									 game.pauseMenu.highlightedOption == PauseMenuOption::Continue ? 
									 PauseMenuOption::Quit : PauseMenuOption::Continue );
		}
		if( game.userCmd.states[static_cast<size_t>( Cmds::Confirm )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuSelectedSound, 0 );
			if( game.pauseMenu.highlightedOption == PauseMenuOption::Quit )
			{
				game.quit = true;
			}
			else
			{
				Game_EndPause( game );
			}
		}
	}
	else if( game.gameState == GameState::GameOver )
	{
		if( game.userCmd.states[static_cast<size_t>( Cmds::Confirm )].pressedThisFrame )
		{
			Mix_PlayChannel( -1, game.menuSelectedSound, 0 );
			Game_EndGameOver( game );
		}
	}
}


static void Game_LoadSounds( Game& game )
{
	game.pieceFallSound		= Mix_LoadWAV( "Data/Sounds/PieceFall.ogg" );
	game.pieceHoldSound		= Mix_LoadWAV( "Data/Sounds/PieceHold.ogg" );
	game.pieceRotateSound	= Mix_LoadWAV( "Data/Sounds/PieceRotate.ogg" );
	game.pieceSoftDropSound = Mix_LoadWAV( "Data/Sounds/PieceSoftDrop.ogg" );
	game.pieceHardDropSound	= Mix_LoadWAV( "Data/Sounds/PieceHardDrop.ogg" );

	game.menuHighlightChanegSound	= Mix_LoadWAV( "Data/Sounds/MenuHighlightChange.ogg" );
	game.menuSelectedSound			= Mix_LoadWAV( "Data/Sounds/MenuSelected.ogg" );

	game.clearSingleDoubleSound = Mix_LoadWAV( "Data/Sounds/ClearSingleDouble.ogg" );
	game.clearTripleSound		= Mix_LoadWAV( "Data/Sounds/ClearTriple.ogg" );
	game.clearTetrisSound		= Mix_LoadWAV( "Data/Sounds/ClearTetris.ogg" );

	game.inGameMusic			= Mix_LoadMUS( "Data/Music/InGame.ogg" );
}


static void Game_UnloadSounds( Game& game )
{
	Mix_FreeChunk( game.pieceFallSound );
	Mix_FreeChunk( game.pieceHoldSound );
	Mix_FreeChunk( game.pieceRotateSound );
	Mix_FreeChunk( game.pieceSoftDropSound );
	Mix_FreeChunk( game.pieceHardDropSound );

	Mix_FreeChunk( game.menuHighlightChanegSound );
	Mix_FreeChunk( game.menuSelectedSound );

	Mix_FreeChunk( game.clearSingleDoubleSound );
	Mix_FreeChunk( game.clearTripleSound );
	Mix_FreeChunk( game.clearTetrisSound );

	Mix_FreeMusic( game.inGameMusic );
}


SDL_Point Game_GetResoltuion( Game& game )
{
	SDL_Point		resolution = { -1, -1 };
	SDL_GetWindowSize( game.window, &resolution.x, &resolution.y );
	return resolution;
}


void Game_New( Game& game )
{
	game.currentFormation = nullptr;
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	if( TTF_Init() != 0 )
	{
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) )
	{
		std::cout << "Mix_OpenAudio Error: " << SDL_GetError() << std::endl;
		return;
	}

	game.window = SDL_CreateWindow( "Game", 100, 100, 800, 600, SDL_WINDOW_SHOWN );
	if ( game.window == nullptr )
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	std::srand( ( unsigned int )game.window );

	game.renderer = SDL_CreateRenderer( game.window, -1,
										SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( game.renderer == nullptr )
	{
		SDL_DestroyWindow( game.window );
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	game.font = TTF_OpenFont( "Data/Fonts/stocky.ttf", 24 );
	if( game.font == nullptr )
	{
		SDL_DestroyRenderer( game.renderer );
		SDL_DestroyWindow( game.window );
		std::cout << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	UserCmd_New( game.userCmd );

	Board_New( game.board );
	Game_ConstructTetrisPieces( game );
	Score_New( game.score, game.renderer, game.font );
	Level_New( game.level, game.renderer, game.font );
	MainMenu_New( game.mainMenu, game.renderer, game.font );
	PauseMenu_New( game.pauseMenu, game.renderer, game.font );

	game.blockTexture = nullptr;
	game.blockTexture = IMG_LoadTexture( game.renderer, "Data/Textures/Block.png" );
	SDL_SetTextureBlendMode( game.blockTexture, SDL_BLENDMODE_BLEND );

	Game_LoadSounds( game );

	GameOverDisplay_New( game.gameOverDisplay, game.renderer, game.font, ScoreBoardFileName );

	Mix_PlayMusic( game.inGameMusic, -1 );
	Game_StartMainMenu( game );
}


void Game_Run( Game& game )
{
	SDL_Event e;
	game.quit				= false;
	auto	  startTime		= SDL_GetTicks() / 1000.0;
	auto	  lastFrameTime	= SDL_GetTicks() / 1000.0;
	while( !game.quit )
	{
		auto frameStartTime = SDL_GetTicks() / 1000.0;

		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
			{
				game.quit = true;
			}
		}

		UserCmd_Tick( game.userCmd, lastFrameTime );
		Game_ProcessInput( game );
		Game_Tick( game, lastFrameTime );
		SDL_RenderClear( game.renderer );
		Game_Draw( game );
		SDL_RenderPresent( game.renderer );

		// Sleep for excess time if there is any. This caps the fps.
		double excessTime = MaxFramePeriod - ( ( SDL_GetTicks() / 1000.0 ) - frameStartTime );
		if( excessTime > 0.0 )
		{
			SDL_Delay( static_cast<Uint32>( excessTime * 1000.0 ) );
		}

		lastFrameTime = ( SDL_GetTicks() / 1000.0 ) - frameStartTime;
	}
}


void Game_Tick( Game& game, float deltaTime )
{
	if( game.gameState == GameState::Playing )
	{
		game.board.fallTime = game.level.speedMultiplier;
		Board_Tick( game.board, deltaTime, &game.hold, &game.score, &game.level,
					game.pieceFallSound, game.clearSingleDoubleSound, game.clearTripleSound,
					game.clearTetrisSound, game.pieceSoftDropSound );

		// Check if we need to add a new piece.
		if( game.board.state == BoardState::Live && !Board_IsPieceFalling( game.board ) )
		{
			game.currentFormation = Game_PushBackQueue( game );
			Board_NewPiece( game.board, *game.currentFormation );
		}
		else if( game.board.state == BoardState::GameOver )
		{
			game.gameOverDisplay.isHighScorer = ScoreBoard_Submit( game.gameOverDisplay.scoreBoard, game.score.value,
																	game.renderer, game.font );
			Game_EndPlaying( game );
		}
	}
}


void Game_Draw( Game& game )
{
	SDL_Point resolution = Game_GetResoltuion( game );

	SDL_Point boardOrigin;
	boardOrigin.x = ( resolution.x / 2 ) - ( ( LineWidth * BlockWidth ) / 2 );
	boardOrigin.y = ( resolution.y / 2 ) - ( ( BoardHeight * BlockHeight ) / 2 );
	Board_Draw( game.board, game.renderer, game.blockTexture, boardOrigin );

	SDL_Rect holdOrigin;
	holdOrigin.x = 50;
	holdOrigin.y = 50;
	Hold_Draw( game.hold, game.renderer, game.blockTexture, holdOrigin );

	SDL_Rect queueOrigin;
	queueOrigin.x = ( resolution.x - 50 ) - ( PieceQueueSize * BlockWidth );
	queueOrigin.y = 50;	
	PieceQueue_Draw( game.pieceQueue, game.renderer, game.blockTexture, queueOrigin );

	SDL_Rect scoreOrigin;
	scoreOrigin.x = 125;
	scoreOrigin.y = 200;
	Score_Draw( game.score, game.renderer, game.font, scoreOrigin );

	SDL_Point levelOrigin;
	levelOrigin.x = 125;
	levelOrigin.y = scoreOrigin.y + game.score.titleSize.y + game.score.scoreSize.y + 50;
	Level_Draw( game.level, game.renderer, levelOrigin, game.font );

	if( game.gameState == GameState::MainMenu )
	{
		SDL_Rect mainMenuOrigin;
		mainMenuOrigin.x = boardOrigin.x + ( BlockWidth * ( LineWidth / 2 ) ) - ( game.mainMenu.playOptionSize.x / 2.0f );
		mainMenuOrigin.y = boardOrigin.y + ( BlockHeight * ( BoardHeight / 2 ) ) - ( game.mainMenu.playOptionSize.y / 2.0f );
		MainMenu_Draw( game.mainMenu, game.renderer, mainMenuOrigin );
	}
	else if( game.gameState == GameState::Paused )
	{
		SDL_Point pauseMenuOrigin;
		pauseMenuOrigin.x = boardOrigin.x + ( BlockWidth * ( LineWidth / 2 ) );
		pauseMenuOrigin.y = boardOrigin.y + ( BlockHeight * ( BoardHeight / 2 ) );
		PauseMenu_Draw( game.pauseMenu, game.renderer, pauseMenuOrigin );
	}
	else if( game.gameState == GameState::GameOver )
	{
		SDL_Point gameOverDisplayOrigin;
		gameOverDisplayOrigin.x = boardOrigin.x + ( BlockWidth * ( LineWidth / 2 ) );
		gameOverDisplayOrigin.y = boardOrigin.y + ( BlockHeight * ( BoardHeight / 3 ) );
		GameOverDisplay_Draw( game.gameOverDisplay, game.renderer, gameOverDisplayOrigin );
	}
}


void Game_Destroy( Game& game )
{
	// Save and destroy game over and score board.
	GameOverDisplay_Destroy( game.gameOverDisplay, ScoreBoardFileName );

	Score_Destroy( game.score );
	MainMenu_Destroy( game.mainMenu );
	SDL_DestroyWindow( game.window );
	SDL_DestroyRenderer( game.renderer );
	Mix_CloseAudio();

	SDL_Quit();
}