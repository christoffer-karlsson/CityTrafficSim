// winprocedure.h: Callback function to handle signals from the Windows OS.

#pragma once

#include "keyboard.h"
#include "mouse.h"
#include "global_device_info.h"

#include <windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM W_Param, LPARAM L_Param);
