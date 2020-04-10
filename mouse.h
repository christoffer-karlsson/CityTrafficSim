// mouse.h: Stores the state of mouse, both in window X,Y coordinate space and raw input.

#pragma once

#include "common.h"
#include "global_device_info.h"

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
	bool Button[255];
};

void UpdateMouse(LPARAM LParam, WPARAM WParam);
void UpdateRawMouse(real32 X, real32 Y);

real32 GetMouseX();
real32 GetMouseY();
real32 GetMouseRawX();
real32 GetMouseRawY();

bool MousePressed(int32 ButtonCode);