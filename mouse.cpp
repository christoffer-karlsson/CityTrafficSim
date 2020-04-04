#include "mouse.h"

static mouse_state Mouse = {};

void UpdateMouse(int32 X, int32 Y, int32 ButtonCode, bool Status)
{
	Mouse.X = X;
	Mouse.Y = Y;

	Mouse.Button[ButtonCode] = Status;
}

void UpdateRawMouse(int32 X, int32 Y)
{
	Mouse.RawX = X;
	Mouse.RawY = Y;
}

int32 GetMouseX()
{
	return Mouse.X;
}

int32 GetMouseY()
{
	// NOTE(Cristoffer): Invert zero location for Y.
	return global_device_info::WindowHeight - Mouse.Y;
}

int32 GetMouseRawX()
{
	// TODO(Cristoffer): Clearing raw input to zero everytime its being fetched makes
	// it so that it only can get fetched once per frame. Think about this later down
	// the road!!
	// Problem solved by this: Removing "gliding" caused by old input.

	int32 Result = Mouse.RawX;

	Mouse.RawX = 0;

	return Result;
}

int32 GetMouseRawY()
{
	int32 Result = Mouse.RawY;

	Mouse.RawY = 0;

	return Result;
}

bool MouseButtonPressed(int32 ButtonCode)
{
	return Mouse.Button[ButtonCode];
}