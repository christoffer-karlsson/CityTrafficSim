// keyboard.h: Handles OS key states and stores them.

#pragma once

#include "common.h"

struct key_state
{
	bool IsDown = 0;
	bool WasDown = 0;
};

void UpdateKeyDown(int32 KeyCode);
void UpdateKeyUp(int32 KeyCode);

bool KeyPressed(int32 KeyCode);
bool KeyReleased(int32 KeyCode);

char GetMappedKey(int32 KeyCode);

void Flush();

// NOTE(Cristoffer): Virtual key code definitions.
// Documentation - https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#define KEY_BACKSPACE	0x08
#define KEY_TAB			0x09
#define KEY_ENTER		0x0D
#define KEY_SHIFT		0x10
#define KEY_CONTROL		0x11
#define KEY_ALT			0x12
#define KEY_ESCAPE		0x1B
#define KEY_SPACE		0x20
#define KEY_PAGEUP		0x21
#define KEY_PAGEDOWN	0x22
#define KEY_END			0x23
#define KEY_HOME		0x24
#define KEY_ARROWLEFT	0x25
#define KEY_ARROWUP		0x26
#define KEY_ARROWRIGHT	0x27
#define KEY_ARROWDOWN	0x28
#define KEY_INSERT		0x2D
#define KEY_DELETE		0x2E
#define KEY_0			0x30
#define KEY_1			0x31
#define KEY_2			0x32
#define KEY_3			0x33
#define KEY_4			0x34
#define KEY_5			0x35
#define KEY_6			0x36
#define KEY_7			0x37
#define KEY_8			0x38
#define KEY_9			0x39
#define KEY_A			0x41
#define KEY_B			0x42
#define KEY_C			0x43
#define KEY_D			0x44
#define KEY_E			0x45
#define KEY_F			0x46
#define KEY_G			0x47
#define KEY_H			0x48
#define KEY_I			0x49
#define KEY_J			0x4A
#define KEY_K			0x4B
#define KEY_L			0x4C
#define KEY_M			0x4D
#define KEY_N			0x4E
#define KEY_O			0x4F
#define KEY_P			0x50
#define KEY_Q			0x51
#define KEY_R			0x52
#define KEY_S			0x53
#define KEY_T			0x54
#define KEY_U			0x55
#define KEY_V			0x56
#define KEY_W			0x57
#define KEY_X			0x58
#define KEY_Y			0x59
#define KEY_Z			0x5A
#define KEY_F1			0x70
#define KEY_F2			0x71
#define KEY_F3			0x72
#define KEY_F4			0x73
#define KEY_F5			0x74
#define KEY_F6			0x75
#define KEY_F7			0x76
#define KEY_F8			0x77
#define KEY_F9			0x78
#define KEY_F10			0x79
#define KEY_F11			0x7A
#define KEY_F12			0x7B

#define VK_OEM_4		0xDB
#define VK_OEM_5		0xDC
#define KEY_TILDE		0xDC
#define VK_OEM_6		0xDD
#define VK_OEM_7		0xDE
#define VK_OEM_8		0xDF