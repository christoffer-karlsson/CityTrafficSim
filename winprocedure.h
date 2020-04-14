// winprocedure.h: Callback function to handle signals from the Windows OS.

#pragma once

#include "keyboard.h"
#include "mouse.h"

#include <windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM WParam, LPARAM LParam);
