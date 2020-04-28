#include "winprocedure.h"

#if DEBUG_IMGUI

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif

LRESULT CALLBACK WindowProcedure(HWND WindowHandle, UINT MessageId, WPARAM WParam, LPARAM LParam)
{
	#if DEBUG_IMGUI

	// Leave message to Imgui proc handler first, if imgui procedure handler took care of the message, then this will return.
	if(app_state::GetDebugMenuEnabled() && ImGui_ImplWin32_WndProcHandler(WindowHandle, MessageId, WParam, LParam))
	{
		return true;
	}

	#endif

	if(MessageId == WM_CLOSE)
	{
		// TODO: Handle closing the window.
		OutputDebugStringW(L"WM_CLOSE\n");
	}
	else if(MessageId == WM_SIZE)
	{
		// TODO: Handle resizing of window.

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