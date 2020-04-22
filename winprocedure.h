// winprocedure.h: Callback function to handle signals from the Windows OS.

#pragma once

#include "keyboard.h"
#include "mouse.h"

#if DEBUG_MODE

#include "application_state.h"
#include "external/imgui/imgui_impl_win32.h"

#else

#include <windows.h>
#include <windowsx.h>

#endif

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM WParam, LPARAM LParam);