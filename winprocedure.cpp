#include "winprocedure.h"

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM WParam, LPARAM LParam)
{
	if(MessageId == WM_CLOSE)
	{
		// TODO(Cristoffer): Handle closing the window.
		OutputDebugStringW(L"WM_CLOSE\n");
	}
	else if(MessageId == WM_SIZE)
	{
		// TODO(Cristoffer): Handle resizing of window.
		global_device_info::WindowWidth = GET_X_LPARAM(LParam);
		global_device_info::WindowHeight = GET_Y_LPARAM(LParam);

	}
	else if(MessageId == WM_KEYDOWN)
	{
		UpdateKeyDown(WParam);
	}
	else if(MessageId == WM_KEYUP)
	{
		UpdateKeyUp(WParam);
	}
	else if(MessageId == WM_LBUTTONDOWN)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_RBUTTONDOWN)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_MBUTTONDOWN)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_LBUTTONUP)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_RBUTTONUP)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_MBUTTONUP)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_MOUSEMOVE)
	{
		UpdateMouse(LParam, WParam);
	}
	else if(MessageId == WM_MOUSEWHEEL)
	{
		UpdateMouseScroll(LParam, WParam);
	}
	else if(MessageId == WM_INPUT)
	{
		// NOTE(Cristoffer): For 32-bit
		//UINT dwSize = 40;
		//static BYTE lpb[40];

		// NOTE(Cristoffer): For 64-bit
		UINT dwSize = 48;
		static BYTE lpb[48];

		GetRawInputData((HRAWINPUT)LParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT *RawInput = (RAWINPUT *)lpb;

		if(RawInput->header.dwType == RIM_TYPEMOUSE)
		{
			real32 RawDeltaX = (real32)RawInput->data.mouse.lLastX;
			real32 RawDeltaY = (real32)RawInput->data.mouse.lLastY;

			UpdateRawMouse(RawDeltaX, RawDeltaY);
		}
	}
	else
	{
		return DefWindowProc(WindowHandle, MessageId, WParam, LParam);
	}

	return 0;
}