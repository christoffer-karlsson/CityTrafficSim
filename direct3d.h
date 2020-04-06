// d3d.h: Direct3d pipeline
// Documentation used: https://docs.microsoft.com/en-us/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11

#pragma once

#include "common.h"
#include "diagnostics.h"
#include "global_device_info.h"
#include "building.h"
#include "terrain.h"
#include "line.h"
#include "world.h"
#include "mouse_picker.h"

#include "external/SpriteFont.h"
#include "external/SimpleMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX::SimpleMath;

class direct3d
{
	private:

	HWND WindowHandle = nullptr;

	D3D11_VIEWPORT Viewport;

	ID3D11Device *Device = nullptr;
	IDXGISwapChain *Swap = nullptr;
	ID3D11DeviceContext *Context = nullptr;
	ID3D11RenderTargetView *Target = nullptr;

	ID3D11Texture2D *DepthStencilBuffer;
	ID3D11DepthStencilState *DepthStencilState;
	ID3D11DepthStencilView *DepthStencilView;
	ID3D11BlendState *AlphaBlendState;

	// NOTE(Cristoffer): Temporary data here ////////////////

	camera Camera;

	

	std::unique_ptr<terrain> Terrain;

	std::vector<std::unique_ptr<drawable>> Graph;

	std::unique_ptr<drawable> TestEntity;;

	world *World = new world(100, 100);

	// NOTE(Cristoffer): Temporary data here ////////////////

	protected:

	void SetDevice();
	void SetFrameBuffer();
	void SetDepthStencil();
	void SetAlphaBlender();
	void SetViewport();

	public:

	std::unique_ptr<SpriteBatch> spriteBatch;
	std::unique_ptr<SpriteFont> spriteFont;

	direct3d(HWND WindowHandle);
	~direct3d();
	direct3d(direct3d const &Object) = delete;
	void operator=(direct3d const &Object) = delete;

	void ClearFrameBuffer(real32 Red, real32 Green, real32 Blue) const;
	void BeginFrame() const;
	void EndFrame() const;

	// TODO(Cristoffer): Temporary methods for testing.
	void BeginSpriteBatch();
	void EndSpriteBatch();
	void DrawSpriteString(const wchar_t *String, real32 PosX, real32 PosY);

	// TODO(Cristoffer): Perhaps camera shouldn't be accessable from here..
	camera &GetCamera();

	void TestDraw();
	void TestDrawEntity(real32 X, real32 Y, real32 Z);
	void TestUpdateBuffer(int32 X, int32 Y);
};