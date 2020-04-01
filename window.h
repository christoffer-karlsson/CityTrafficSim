// window.h: class for constructing the window, and some utility methods related to that

#pragma once

#include "common.h"
#include "winprocedure.h"

#include <windows.h>

class window
{
	private:

	HWND			WindowHandle;
	HINSTANCE		WindowInstance;
	LPCWSTR			WindowClassName;

	void InitRawInputDevice();

	public:

	window(LPCWSTR Title, int32 Width, int32 Height);
	~window();

	HWND GetHandle() const;

	void SetTitle(LPCWSTR Title);

	void ClipMouseCursor(bool Clip);
	void ShowMouseCursor(bool Show);

	DISABLE_INSTANCE_COPY(window)
};