#include "Board.h"
#include "Piece.h"
#include "Hold.h"
#include "Score.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <memory>
#include <cassert>

static Piece* Board_AllocatePiece( Board& board, const PieceFormation& formation )
{
	for( int i = 0; i < MaxPieces; ++i )
	{
		if( !board.pieces[i].active )
		{
			Piece_New( board.pieces[i] );
			board.pieces[i].formation	= formation;
			return &board.pieces[i];
		}
	}

	return nullptr;
}


static void Board_DeallocatePiece( Board& board, Piece& piece )
{
	Piece_Destroy( piece );
}


static void Board_ClearRow( Board& board, int row )
{
	board.lines[row].lineFlags &= ~LineFlagFalling;
	board.lines[row].lineFlags |= LineFlagFading;
}


static void Board_StartClearFalling( Board& board )
{
	board.state					= BoardState::ClearFalling;
	board.currentFallDistance	= 0.0f;
}


static void Board_EndClearFalling( Board& board )
{
	board.state						= BoardState::Live;

	// Remove fading/falling flags.
	for( int i = 0; i < BoardHeight; ++i )
	{
		board.lines[i].lineFlags &= ~LineFlagFading;
		board.lines[i].lineFlags &= ~LineFlagFalling;
	}
}


static void Board_StartClearFading( Board& board )
{
	board.state					= BoardState::ClearFading;
	board.currentClearAlpha		= 0xFF;
	board.targetClearAlpha		= 0x00;
}


static void Board_EndClearFading( Board& board )
{
	// Deactivate cleared lines.
	for( int i = 0; i < BoardHeight; ++i )
	{
		if( board.lines[i].lineFlags & LineFlagFading )
		{
			Line_Deactivate( board.lines[i] );
		}
	}

	// Flag all lines that need to fall.
	bool found = false;
	for( int i = BoardHeight - 1; i >= 0; --i )
	{
		if( board.lines[i].lineFlags & LineFlagFading )
		{
			found = true;
		}
		else if( found )
		{
			board.lines[i].lineFlags |= LineFlagFalling;
		}
	}

	// Start falling.
	Board_StartClearFalling( board );
}


static void Board_StartGameOver( Board& board )
{
	board.state = BoardState::GameOver;
}


static void Board_StartGameOverEffect( Board& board )
{
	board.state								= BoardState::GameOverEffect;
	board.currentGameOverEffectBlockTime	= 0.0f;
	board.lastGameOverEffectBlockX			= LineWidth - 1;
	board.lastGameOverEffectBlockY			= BoardHeight - 1;

	// Get rid of the falling piece if there still is one.
	auto fallingPiece = Board_GetFirstFallingPiece( board );
	if( fallingPiece != nullptr )
	{
		Board_DestroyPiece( board, *fallingPiece, nullptr, nullptr, nullptr, nullptr, nullptr );
	}
}


static void Board_EndGameOverEffect( Board& board )
{
	board.state								= BoardState::GameOver;
	Board_StartGameOver( board );
}


static void Board_StartStartGameEffect( Board& board )
{
	board.state								= BoardState::StartGameEffect;
	board.currentGameOverEffectBlockTime	= 0.0f;
	board.lastGameOverEffectBlockX			= 0;
	board.lastGameOverEffectBlockY			= 0;
}


static void Board_EndStartGameEffect( Board& board )
{
	board.state								= BoardState::Live;
}


static void Board_TickStartGameEffect( Board& board, float deltaTime )
{
	// Just undo game over effect.
	board.currentGameOverEffectBlockTime += deltaTime;
	while( board.currentGameOverEffectBlockTime >= BoardGameOverEffectBlockTime )
	{
		board.currentGameOverEffectBlockTime -= BoardGameOverEffectBlockTime;
		
		auto& block = board.lines[board.lastGameOverEffectBlockY].blocks[board.lastGameOverEffectBlockX];
		block.active = false;

		if( board.lastGameOverEffectBlockY % 2 == 0 )
		{
			++board.lastGameOverEffectBlockX;
			if( board.lastGameOverEffectBlockX >= LineWidth )
			{
				board.lastGameOverEffectBlockX = LineWidth - 1;
				++board.lastGameOverEffectBlockY;
			}
		}
		else
		{
			--board.lastGameOverEffectBlockX;
			if( board.lastGameOverEffectBlockX < 0 )
			{
				board.lastGameOverEffectBlockX = 0 ;
				++board.lastGameOverEffectBlockY;
			}
		}

		if( board.lastGameOverEffectBlockY >= BoardHeight )
		{
			Board_EndStartGameEffect( board );
		}
	}
}


static void Board_TickGameOverEffect( Board& board, float deltaTime )
{
	board.currentGameOverEffectBlockTime += deltaTime;
	while( board.currentGameOverEffectBlockTime >= BoardGameOverEffectBlockTime )
	{
		board.currentGameOverEffectBlockTime -= BoardGameOverEffectBlockTime;
		
		auto& block = board.lines[board.lastGameOverEffectBlockY].blocks[board.lastGameOverEffectBlockX];
		block.active = true;
		block.colour = 0x007F7F7F;

		// Place blocks in each spot until we run out. Make sure we alternate
		// x directions as we go up the lines. It looks nicer.
		if( board.lastGameOverEffectBlockY % 2 == 0 )
		{
			++board.lastGameOverEffectBlockX;
			if( board.lastGameOverEffectBlockX >= LineWidth )
			{
				board.lastGameOverEffectBlockX = LineWidth - 1;
				--board.lastGameOverEffectBlockY;
			}
		}
		else
		{
			--board.lastGameOverEffectBlockX;
			if( board.lastGameOverEffectBlockX < 0 )
			{
				board.lastGameOverEffectBlockX = 0 ;
				--board.lastGameOverEffectBlockY;
			}
		}

		if( board.lastGameOverEffectBlockY < 0 )
		{
			// No more blocks to fill...
			Board_EndGameOverEffect( board );
		}
	}
}


static int Board_ClearLines( Board& board )
{
	// Check for cleared lines.
	int cleared = 0;
	for( int y = BoardHeight - 1; y >= 0; --y )
	{
		if( Line_IsCleared( board.lines[y] ) )
		{
			++cleared;
			Board_ClearRow( board, y );
			for( int i = 0; i < LineWidth; ++i )
			{
				Block_StartFlash( board.lines[y].blocks[i] );
			}
		}
	}

	// If a line has been cleared, start falling.
	if( cleared > 0 )
	{
		Board_StartClearFading( board );
	}
	return cleared;
}


bool Board_CanAddPiece( const Board& board, const Piece& piece )
{
	for( int x = 0; x < PieceWidth; ++x )
	{
		for( int y = 0; y < PieceHeight; ++y )
		{
			if( piece.formation.blocks[x][y].active && ( piece.x + x >= LineWidth 
				|| piece.y + y >= BoardHeight || piece.x + x < 0 || piece.y + y < 0 ) )
			{
				return false;
			}

			if( board.lines[piece.y + y].blocks[piece.x + x].active && piece.formation.blocks[x][y].active )
			{
				// Overlap, this piece can't be added.
				return false;
			}
		}
	}

	// No collisions.
	return true;
}


void Board_New( Board& board )
{
	std::memset( board.lines, 0, sizeof( board.lines ) );
	std::memset( board.pieces, 0, sizeof( board.pieces ) );
	board.fallTime = InitialFallTime;
	board.state	   = BoardState::Live;

	for( int y = 0; y < BoardHeight; ++y )
	{
		for( int x = 0; x < LineWidth; ++x )
		{
			board.lines[y].blocks[x].colour = 0x007F7F7F;
			board.lines[y].blocks[x].active = true;
		}
	}
}


void Board_Tick( Board& board, float deltaTime, Hold* hold, Score* score, Level* level,
				 Mix_Chunk* pieceFallSound, Mix_Chunk* singleDoubleClearSound,
				 Mix_Chunk* tripleClearSound, Mix_Chunk* tetrisClearSound,
				 Mix_Chunk* softDropSound )
{
	if( board.state == BoardState::Live )
	{
		// Tick all active pieces.
		for( int i = 0; i < MaxPieces; ++i )
		{
			if( board.pieces[i].active )
			{
				Piece_Tick( board.pieces[i], deltaTime );

				// Time for this piece to fall?
				if( board.pieces[i].isFalling && board.pieces[i].nextFall <= 0.0f )
				{
					if( !Board_TryPieceFall( board, board.pieces[i], score, level,
											 singleDoubleClearSound, tripleClearSound, 
											 tetrisClearSound ) && hold != nullptr )
					{
						if( softDropSound != nullptr )
						{
							Mix_PlayChannel( -1, softDropSound, 0 );
						}
						Hold_ResetHold( *hold );
					}
					else
					{
						if( pieceFallSound != nullptr )
						{
							Mix_PlayChannel( -1, pieceFallSound, 0 );
						}
					}
				}
			}
		}
	}
	else if( board.state == BoardState::ClearFading )
	{
		float a = board.currentClearAlpha;
		a -= deltaTime * LineFadeSpeed;
		if( a <= board.targetClearAlpha )
		{
			Board_EndClearFading( board );
		}
		board.currentClearAlpha = a;
	}
	else if( board.state == BoardState::ClearFalling )
	{
		// Have we hit the ground?
		board.currentFallDistance += deltaTime * LineFallSpeed;

		// Go backwards throw the lines and swap them into the right places.
		int linesToFall = 0;
		bool anyFalling = false;
		for( int i = BoardHeight - 1; i >= 0; --i )
		{
			if( board.lines[i].lineFlags & LineFlagFading )
			{
				++linesToFall;
			}
			else if( board.lines[i].lineFlags & LineFlagFalling )
			{
				if( board.currentFallDistance >= linesToFall * BlockHeight )
				{
					board.lines[i].lineFlags &= ~LineFlagFalling;
					std::swap( board.lines[i], board.lines[i + linesToFall] );
				}
				else
				{
					anyFalling = true;
				}
			}
		}

		if( !anyFalling )
		{
			Board_EndClearFalling( board );
		}
	}
	else if( board.state == BoardState::GameOverEffect )
	{
		Board_TickGameOverEffect( board, deltaTime );
	}
	else if( board.state == BoardState::StartGameEffect )
	{
		Board_TickStartGameEffect( board, deltaTime );
	}
	
	for( int i = 0; i < BoardHeight; ++i )
	{
		Line_Tick( board.lines[i], deltaTime );
	}
}


void Board_Draw( Board& board, SDL_Renderer* renderer,
				SDL_Texture* blockTexture, const SDL_Point& origin )
{
	int boardStartX			= origin.x;
	int boardStartY			= origin.y;
	
	SDL_Rect dstRect;
	dstRect.w = BlockWidth;
	dstRect.h = BlockHeight;

	SDL_SetTextureColorMod( blockTexture, 0x7F, 0x7F, 0x7F );

	// Draw outline walls.
	for( int y = 0; y < BoardHeight; ++y )
	{
		dstRect.y = y * BlockHeight + boardStartY;

		dstRect.x = boardStartX - BlockWidth;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dstRect );

		dstRect.x = boardStartX + LineWidth * BlockWidth;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dstRect );
	}

	dstRect.y = boardStartY + ( BoardHeight ) * BlockHeight;

	// Draw outline bottom.
	for( int x = -1; x < LineWidth + 1; x++ )
	{
		dstRect.x = boardStartX + BlockWidth * x;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dstRect );
	}

	// Draw the filled in board.
	for( int y = 0; y < BoardHeight; ++y )
	{
		// Is line fading?
		if( board.lines[y].lineFlags & LineFlagFading )
		{
			SDL_SetTextureAlphaMod( blockTexture, board.currentClearAlpha );
		}
		else
		{
			SDL_SetTextureAlphaMod( blockTexture, 0xFF );
		}

		for( int x = 0; x < LineWidth; x++ )
		{
			if( board.lines[y].blocks[x].active )
			{
				SDL_SetTextureColorMod( blockTexture, ( board.lines[y].blocks[x].colour & RedMask ) >> 16,
										( board.lines[y].blocks[x].colour & GreenMask ) >> 8,
										  board.lines[y].blocks[x].colour & BlueMask );

				dstRect.x = boardStartX + BlockWidth * x;
				dstRect.y = boardStartY + BlockHeight * y;

				// Fall offset.
				if( board.state == BoardState::ClearFalling 
					&& board.lines[y].lineFlags & LineFlagFalling )
				{
					dstRect.y += board.currentFallDistance;
				}

				SDL_RenderCopy( renderer, blockTexture, nullptr, &dstRect );
			}
		}
	}
	SDL_SetTextureAlphaMod( blockTexture, 0xFF );


	// Draw falling piece shadow.
	auto fallingPiece = Board_GetFirstFallingPiece( board );
	if( fallingPiece != nullptr )
	{
		auto shadow	= *fallingPiece;

		Board_RemovePiece( board, *fallingPiece );
		Board_DropPiece( board, shadow );
		Board_AddPiece( board, *fallingPiece );

		SDL_SetTextureAlphaMod( blockTexture, 0x3F );

		SDL_Rect origin;
		origin.x = boardStartX + shadow.x * BlockWidth;
		origin.y = boardStartY + shadow.y * BlockHeight;
		PieceFormation_Draw( shadow.formation, renderer, blockTexture, origin );
		SDL_SetTextureAlphaMod( blockTexture, 0xFF );
	}
}


bool Board_TryPieceFall( Board& board, Piece& piece, Score* score, Level* level,
						Mix_Chunk* singleDoubleClearSound, Mix_Chunk* tripleClearSound,
						Mix_Chunk* tetrisClearSound )
{
	if( !Board_AdjustPiecePosition( board, piece, 0, 1 ) )
	{
		Board_DestroyPiece( board, piece, score, level, singleDoubleClearSound, tripleClearSound,
							tetrisClearSound );
		return false;
	}
	else
	{
		// If we're one step from landing, make sure we use initial time.
		// This makes it possible to actually play faster speeds.
		Board_RemovePiece( board, piece );
		piece.y += 1;
		bool landNextFall = !Board_CanAddPiece( board, piece );
		piece.y -= 1;
		Board_AddPiece( board, piece );

		if( !landNextFall )
		{
			piece.nextFall = board.fallTime;
		}
		else
		{
			piece.nextFall = InitialFallTime;
		}
		return true;
	}
}


bool Board_AdjustPiecePosition( Board& board, Piece& piece, int deltaX, int deltaY )
{
	Piece shadow;
	std::memcpy( &shadow, &piece, sizeof( Piece ) );

	shadow.x += deltaX;
	shadow.y += deltaY;

	Board_RemovePiece( board, piece );

	if( Board_CanAddPiece( board, shadow ) )
	{
		// Fall one block down.
		Board_AddPiece( board, shadow );
		piece.x += deltaX;
		piece.y += deltaY;

		return true;
	}

	Board_AddPiece( board, piece );
	return false;
}


void Board_DropPiece( const Board& board, Piece& piece )
{
	while( Board_CanAddPiece( board, piece ) )
	{
		++piece.y;
	}
	--piece.y;
}


bool Board_RotatePiece( Board& board, Piece& piece, PieceRotation rotation )
{
	Piece shadow = piece;
	
	Piece_Rotate( shadow, rotation );
	Board_RemovePiece( board, piece );

	if( Board_CanAddPiece( board, shadow ) )
	{
		Piece_Rotate( piece, rotation );
		Board_AddPiece( board, piece );
		return true;
	}

	Board_AddPiece( board, piece );
	return false;
}


bool Board_NewPiece( Board& board, const PieceFormation& formation )
{
	auto newPiece = Board_AllocatePiece( board, formation );
	newPiece->isFalling = true;
	newPiece->x			= PieceStartX;
	newPiece->y			= PieceStartY;
	newPiece->nextFall	= board.fallTime;
	if( !Board_CanAddPiece( board, *newPiece ) )
	{
		Board_StartGameOverEffect( board );
		return false;
	}

	Board_AddPiece( board, *newPiece );
	return true;
}


void Board_DestroyPiece( Board& board, Piece& piece, Score* score, Level* level,
						Mix_Chunk* singleDoubleClearSound, Mix_Chunk* tripleClearSound,
						Mix_Chunk* tetrisClearSound )
{
	// Only time we can clear lines is when a piece was remove from the active list.
	// Clear all complete lines now.
	int clearedLines = Board_ClearLines( board );
	if( clearedLines > 0 )
	{
		// Add score for clearing.
		if( score != nullptr )
		{
			Score_Add( *score, clearedLines * clearedLines * 100 );
			if( level != nullptr )
			{
				Level_SetLevel( *level, score->value  / 1000.0f );
			}
		}

		if( ( clearedLines == 1 || clearedLines == 2 ) && singleDoubleClearSound != nullptr )
		{
			Mix_PlayChannel( -1, singleDoubleClearSound, 0 );
		}
		else if( clearedLines == 3 && tripleClearSound != nullptr )
		{
			Mix_PlayChannel( -1, tripleClearSound, 0 );
		}
		else if( clearedLines == 4 && tetrisClearSound != nullptr )
		{
			Mix_PlayChannel( -1, tetrisClearSound, 0 );
		}
	}
	else
	{
		// Make the piece flash to indicate it has landed. Only do this if we
		// have not cleared a line, since all cleared lines flash in that case
		// instead.
		for( int y = 0; y < PieceHeight; ++y )
		{
			for( int x = 0; x < PieceWidth; ++x )
			{
				auto bx = piece.x + x;
				auto by = piece.y + y;
				if( bx < 0 || bx >= LineWidth || by < 0 || by >= BoardHeight )
				{
					continue;
				}

				auto& block = board.lines[by].blocks[bx];
				if( block.active && piece.formation.blocks[x][y].active )
				{
					Block_StartFlash( block );
				}
			}
		}
	}

	// Stop falling. Remove the piece from the list. The blocks will still be on the
	// board.
	Piece_StopFalling( piece );
	Board_DeallocatePiece( board, piece );
}


void Board_Reset( Board& board )
{
	Board_StartStartGameEffect( board );
}


Piece* Board_GetFirstFallingPiece( Board& board )
{
	for( int i = 0; i < MaxPieces; ++i )
	{
		if( board.pieces[i].active && board.pieces[i].isFalling )
		{
			return &board.pieces[i];
		}
	}
	return nullptr;
}


bool Board_IsPieceFalling( Board& board )
{
	return Board_GetFirstFallingPiece( board ) != nullptr;
}


void Board_RemovePiece( Board& board, const Piece& piece )
{
	// Remove the pieces on the board.
	for( int x = 0; x < PieceWidth; ++x )
	{
		for( int y = 0; y < PieceHeight; ++y )
		{
			if( piece.formation.blocks[x][y].active )
			{
				board.lines[piece.y + y].blocks[piece.x + x].active = false;
			}
		}
	}
}


void Board_AddPiece( Board& board, const Piece& piece )
{
	// Add the board pieces.
	for( int x = 0; x < PieceWidth; ++x )
	{
		for( int y = 0; y < PieceHeight; ++y )
		{
			if( piece.x + x >= LineWidth || piece.y + y >= BoardHeight || piece.x + x < 0 || piece.y + y < 0 )
			{
				assert( !piece.formation.blocks[x][y].active );
				continue;
			}
			if( piece.formation.blocks[x][y].active )
			{
				assert( !board.lines[piece.y + y].blocks[piece.x + x].active );
				board.lines[piece.y + y].blocks[piece.x + x] = piece.formation.blocks[x][y];
			}
		}
	}
}