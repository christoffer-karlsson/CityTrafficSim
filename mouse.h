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
	int32 X = 0;
	int32 Y = 0;
	int32 RawX = 0;
	int32 RawY = 0;
	bool Button[255];
};

void UpdateMouse(int32 LParam, int32 WParam);
void UpdateRawMouse(int32 X, int32 Y);

int32 GetMouseX();
int32 GetMouseY();
int32 GetMouseRawX();
int32 GetMouseRawY();

bool MousePressed(int32 ButtonCode);