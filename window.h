// window.h: class for constructing the window, and some utility methods related to the window itself

#pragma once

#include "common.h"
#include "winprocedure.h"
#include "direct3d.h"

#include <windows.h>

class window
{
	private:

	HWND			WindowHandle;
	HINSTANCE		WindowInstance;

	direct3d		Direct3D;

	void InitRawInputDevice();
	void InitGraphicsDevice();

	public:

	window(const char *Title, int32 Width, int32 Height);
	~window() = default;
	window(window const &Object) = delete;
	void operator=(window const &Object) = delete;

	HWND GetHandle() const;
	direct3d &GetGraphicsDevice();

	void SetTitle(const char *Title);

	void ClipMouseCursor(bool Clip);
	void ShowMouseCursor(bool Show);
};