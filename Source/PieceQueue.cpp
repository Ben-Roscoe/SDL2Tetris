#include "PieceQueue.h"
#include "Block.h"
#include <memory>
#include <SDL.h>


void PieceQueue_New( PieceQueue& pieceQueue )
{
	static_assert( PieceQueueSize > 0, "Piece queue size must be larger than 0." );

	// Initialise queue to null.
	std::memset( pieceQueue.queue, 0, sizeof( pieceQueue.queue ) );
}


PieceFormation* PieceQueue_PushBack( PieceQueue& pieceQueue, PieceFormation* formation )
{
	auto out = pieceQueue.queue[0];
	for( int i = 1; i < PieceQueueSize; ++i )
	{
		pieceQueue.queue[i - 1] = pieceQueue.queue[i];
	}
	pieceQueue.queue[PieceQueueSize - 1] = formation;
	return out;
}


void PieceQueue_Clear( PieceQueue& pieceQueue )
{
	for( int i = 0; i < PieceQueueSize; ++i )
	{
		pieceQueue.queue[i] = nullptr;
	}
}


void PieceQueue_Draw( PieceQueue& pieceQueue, SDL_Renderer* renderer, SDL_Texture* blockTexture, const SDL_Rect& origin )
{
	SDL_Rect dst;
	dst.w = BlockWidth;
	dst.h = BlockHeight;

	const int PieceQueueHeight = BlockHeight * ( PieceHeight * PieceQueueSize );

	// Draw top/bottom.
	SDL_SetTextureColorMod( blockTexture, 0x7F, 0x7F, 0x7F );
	for( int i = 0; i <= PieceQueueWidth; ++i )
	{
		dst.x = origin.x + ( i * BlockWidth );

		dst.y = origin.y - BlockHeight * 2;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );

		// Put the next formation in it's own sections.
		dst.y = origin.y + ( PieceHeight - 1 ) * BlockHeight;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );

		dst.y = origin.y + PieceQueueHeight;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );
	}

	// Draw left/right.
	for( int i = 0; i <= PieceQueueSize * PieceHeight + 1; ++i )
	{
		dst.y = origin.y + ( ( i - 1 ) * BlockHeight );

		dst.x = origin.x;
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );

		dst.x = origin.x + ( BlockWidth * PieceQueueWidth );
		SDL_RenderCopy( renderer, blockTexture, nullptr, &dst );
	}

	// Draw queue'd pieces.
	for( int i = 0; i < PieceQueueSize; ++i )
	{
		if( pieceQueue.queue[i] != nullptr )
		{
			dst.x = origin.x + BlockWidth * 2;
			dst.y = origin.y + ( ( i * PieceHeight ) * BlockHeight );
			if( i > 0 )
			{
				dst.y += BlockHeight;
			}
			PieceFormation_Draw( *pieceQueue.queue[i], renderer, blockTexture, dst );
		}
	}
}