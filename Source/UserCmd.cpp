#include "UserCmd.h"


static void CmdState_New( CmdState& cmdState, SDL_Scancode scanCode )
{
	cmdState.isDown				= false;
	cmdState.pressedThisFrame	= false;
	cmdState.activated			= false;
	cmdState.timeTillNextRepeat	= DefaultRepeatDelay;
	cmdState.scanCode			= scanCode;
}


static void CmdState_Tick( CmdState& cmdState, const Uint8* keys, float deltaTime )
{
	// If we were activated last frame, deactivate. This is
	// so we only handle events for this cmd once.
	if( cmdState.activated )
	{
		cmdState.activated = false;
	}

	
	if( keys[cmdState.scanCode] )
	{
		if( cmdState.isDown )
		{
			// Remove pressed this frame flag, since it's been a frame.
			if( cmdState.pressedThisFrame )
			{
				cmdState.pressedThisFrame = false;
			}

			// Countdown til next repeat event.
			cmdState.timeTillNextRepeat -= deltaTime;
			if( cmdState.timeTillNextRepeat <= 0.0f )
			{
				cmdState.activated			= true;
				cmdState.timeTillNextRepeat = DefaultRepeatInterval;
			}
		}
		else
		{
			// New keydown.
			cmdState.isDown				= true;
			cmdState.pressedThisFrame	= true;
			cmdState.activated			= true;
		}
	}
	else
	{
		// Key no longer down.
		if( cmdState.isDown )
		{
			cmdState.isDown				= false;
			cmdState.activated			= false;
			cmdState.pressedThisFrame	= false;
			cmdState.timeTillNextRepeat	= DefaultRepeatDelay;
		}
	}
}


void UserCmd_New( UserCmd& userCmd )
{
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::MoveLeft )], SDL_SCANCODE_LEFT );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::MoveRight )], SDL_SCANCODE_RIGHT );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::FallFaster )], SDL_SCANCODE_DOWN );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::Drop )], SDL_SCANCODE_SPACE );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::RotateRight )], SDL_SCANCODE_UP );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::RotateLeft )], SDL_SCANCODE_V );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::Pause )], SDL_SCANCODE_ESCAPE );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::Confirm )], SDL_SCANCODE_SPACE );
	CmdState_New( userCmd.states[static_cast<size_t>( Cmds::Hold )], SDL_SCANCODE_C );
}


void UserCmd_Tick( UserCmd& userCmd, float deltaTime )
{
	const Uint8* keys = SDL_GetKeyboardState( nullptr );
	for( int i = 0; i < MaxCmdStates; ++i )
	{
		CmdState_Tick( userCmd.states[i], keys, deltaTime );
	}
}