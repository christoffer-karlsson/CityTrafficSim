// d3d_global_device_info.h: globally accessable variables for accessing rendering pipeline device

#pragma once

#include "common.h"

#include <d3d11.h>

// TODO(Cristoffer): Refactor this once rendering pipeline is up and running.

struct global_device_info
{
	static int32 WindowWidth;
	static int32 WindowHeight;

	static const real32 FrameBufferWidth;
	static const real32 FrameBufferHeight;

	static IDXGISwapChain *Swap;
	static ID3D11Device *Device;
	static ID3D11DeviceContext *Context;
	static ID3D11RenderTargetView *Target;
};