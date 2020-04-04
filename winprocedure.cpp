#include "winprocedure.h"

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM W_Param, LPARAM L_Param)
{
	if(MessageId == WM_CLOSE)
	{
		// TODO(Cristoffer): Handle closing the window.
		OutputDebugStringW(L"WM_CLOSE\n");
	}
	else if(MessageId == WM_SIZE)
	{
		// TODO(Cristoffer): Handle resizing of window.
		global_device_info::WindowWidth = GET_X_LPARAM(L_Param);
		global_device_info::WindowHeight = GET_Y_LPARAM(L_Param);

	}
	else if(MessageId == WM_KEYDOWN)
	{
		UpdateKeyDown(W_Param);
	}
	else if(MessageId == WM_KEYUP)
	{
		UpdateKeyUp(W_Param);
	}
	else if(MessageId == WM_LBUTTONDOWN)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 1);
	}
	else if(MessageId == WM_RBUTTONDOWN)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 1);
	}
	else if(MessageId == WM_MBUTTONDOWN)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 1);
	}
	else if(MessageId == WM_LBUTTONUP)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 0);
	}
	else if(MessageId == WM_RBUTTONUP)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 0);
	}
	else if(MessageId == WM_MBUTTONUP)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 0);
	}
	else if(MessageId == WM_MOUSEMOVE)
	{
		int32 X = GET_X_LPARAM(L_Param);
		int32 Y = GET_Y_LPARAM(L_Param);

		UpdateMouse(X, Y, W_Param, 0);
	}
	else if(MessageId == WM_INPUT)
	{
		// NOTE(Cristoffer): For 32-bit
		//UINT dwSize = 40;
		//static BYTE lpb[40];

		// NOTE(Cristoffer): For 64-bit
		UINT dwSize = 48;
		static BYTE lpb[48];

		GetRawInputData((HRAWINPUT)L_Param, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT *RawInput = (RAWINPUT *)lpb;

		if(RawInput->header.dwType == RIM_TYPEMOUSE)
		{
			int RawDeltaX = RawInput->data.mouse.lLastX;
			int RawDeltaY = RawInput->data.mouse.lLastY;

			UpdateRawMouse(RawDeltaX, RawDeltaY);
		}
	}
	else
	{
		return DefWindowProc(WindowHandle, MessageId, W_Param, L_Param);
	}

	return 0;
}