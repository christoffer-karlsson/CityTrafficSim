// mouse.h: Stores the state of mouse, both in window X,Y coordinate space and raw input.

#pragma once

#include "common.h"
#include "global_device_info.h"

#define MBUTTON_LEFT	0x0001
#define MBUTTON_RIGHT	0x0002
#define MBUTTON_MIDDLE	0x0010

struct mouse_state
{
	int32 X = 0;
	int32 Y = 0;
	int32 RawX = 0;
	int32 RawY = 0;
	bool Button[255];
};

void UpdateMouse(int32 X, int32 Y, int32 ButtonCode, bool Status);
void UpdateRawMouse(int32 X, int32 Y);

int32 GetMouseX();
int32 GetMouseY();
int32 GetMouseRawX();
int32 GetMouseRawY();

bool MouseButtonPressed(int32 ButtonCode);