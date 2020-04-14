// mouse.h: Stores the state of mouse, both in window X,Y coordinate space and raw input.

#pragma once

#include "common.h"

#include "windows.h"
#include "windowsx.h"

#define MOUSE_BUTTON_LEFT	0x0001
#define MOUSE_BUTTON_RIGHT	0x0002
#define MOUSE_BUTTON_MIDDLE	0x0010

struct mouse_state
{
	real32 X = 0;
	real32 Y = 0;
	real32 RawX = 0;
	real32 RawY = 0;

	int32 ScrollDelta = 0;
	bool32 ScrollUp = 0;
	bool32 ScrollDown = 0;

	bool32 Button[255];
	bool32 ButtonClick[255];
};

void UpdateMouse(LPARAM LParam, WPARAM WParam);
void UpdateRawMouse(real32 X, real32 Y);
void UpdateMouseScroll(LPARAM LParam, WPARAM WParam);

real32 GetMouseX();
real32 GetMouseY();
real32 GetMouseRawX();
real32 GetMouseRawY();
bool32 GetMouseScrollUp();
bool32 GetMouseScrollDown();

bool32 MousePressed(int32 ButtonCode);
bool32 MouseClicked(int32 ButtonCode);