// Documentation: https://docs.microsoft.com/en-us/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11

/*
==========================================================
	Static class dedicated to setting up the Direct3D
	API pipeline. Call Init() to initiate the device.
	Make the draw calls between BeginFrame() and
	EndFrame(), which will clear and present the buffer.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_diagnostics.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dxgidebug.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX;

class d3d_api
{
	private:

	static HWND						WindowHandle;
	static real32					BufferWidth;
	static real32					BufferHeight;

	static ID3D11Device				*Device;
	static IDXGISwapChain			*Swap;
	static ID3D11DeviceContext		*Context;
	static ID3D11RenderTargetView	*Target;

	static ID3D11Texture2D			*DepthStencilBuffer;
	static ID3D11DepthStencilState	*DepthStencilState;
	static ID3D11DepthStencilView	*DepthStencilView;
	static ID3D11BlendState			*AlphaBlendState;

	static D3D11_VIEWPORT			Viewport;

	protected:

	static void SetDevice();
	static void SetFrameBuffer();
	static void SetDepthStencil();
	static void SetAlphaBlender();
	static void SetViewport();

	public:

	static IDXGIDebug *Debug;

	~d3d_api();

	static void Init(HWND WindowHandle);
	static void BeginFrame();
	static void EndFrame();

	static ID3D11RenderTargetView	*GetTarget();
	static ID3D11DeviceContext		*GetContext();
	static IDXGISwapChain			*GetSwap();
	static ID3D11Device				*GetDevice();

	static ID3D11Texture2D			*GetDepthStencilBuffer();
	static ID3D11DepthStencilState	*GetDepthStencilState();
	static ID3D11DepthStencilView	*GetDepthStencilView();
	static ID3D11BlendState			*GetAlphaBlendState();

	static real32 GetBufferWidth();
	static real32 GetBufferHeight();
};