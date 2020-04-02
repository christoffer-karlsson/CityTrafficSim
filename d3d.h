// d3d.h: Direct3d library setup
// Documentation used: https://docs.microsoft.com/en-us/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11

#pragma once

#include "common.h"
#include "d3d_diagnostics.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

class d3d
{
	private:

	HWND WindowHandle;
	int32 BufferWidth;
	int32 BufferHeight;

	ID3D11Device *Device = nullptr;
	IDXGISwapChain *Swap = nullptr;
	ID3D11DeviceContext *Context = nullptr;
	ID3D11RenderTargetView *Target = nullptr;

	protected:

	void InitializeDevice();

	public:

	d3d(HWND WindowHandle, int32 BufferWidth, int32 BufferHeight);
	~d3d();

	void EndFrame();

	DISABLE_INSTANCE_COPY(d3d);
};