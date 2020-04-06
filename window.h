// window.h: class for constructing the window, and some utility methods related to the window itself

#pragma once

#include "common.h"
#include "winprocedure.h"
#include "global_device_info.h"

#include <windows.h>

class window
{
	private:

	HWND			WindowHandle;

	protected:

	void InitRawInputDevice();

	public:

	window(const char *Title, int32 Width, int32 Height);
	~window() = default;
	window(window const &Object) = delete;
	void operator=(window const &Object) = delete;

	HWND GetHandle() const;

	void SetTitle(const char *Title);

	void ClipMouseCursor(bool Clip);
	void ShowMouseCursor(bool Show);
};