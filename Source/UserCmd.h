#pragma once

#include <SDL.h>

const int	MaxCmdStates			= 9;
const float	DefaultRepeatDelay		= 0.3f;
const float DefaultRepeatInterval	= 0.04f;

enum class Cmds
{
	MoveLeft	= 0,
	MoveRight	= 1,
	FallFaster	= 2,
	Drop		= 3,
	RotateLeft	= 4,
	RotateRight	= 5,
	Pause		= 6,
	Confirm		= 7,
	Hold		= 8,
};


struct CmdState
{
	bool			isDown				= false;
	bool			pressedThisFrame	= false;
	bool			activated			= false;
	float			timeTillNextRepeat	= 0.0f;
	SDL_Scancode	scanCode;
};


// We want to manage our own key repeats here because windows seems
// to cancel a key repeat when another key press occurs. We don't want
// that.
struct UserCmd
{
	CmdState		states[MaxCmdStates];
};


void UserCmd_New( UserCmd& userCmd );
void UserCmd_Tick( UserCmd& userCmd, float deltaTime );