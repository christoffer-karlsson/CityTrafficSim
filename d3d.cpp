#include "d3d.h"

d3d::d3d(HWND WindowHandle, int32 BufferWidth, int32 BufferHeight)
{
	this->WindowHandle = WindowHandle;
	this->BufferWidth = BufferWidth;
	this->BufferHeight = BufferHeight;

	InitializeDevice();
}

d3d::~d3d()
{
	if(Context != nullptr)
	{
		Context->Release();
	}

	if(Device != nullptr)
	{
		Device->Release();
	}

	if(Swap != nullptr)
	{
		Swap->Release();
	}

	if(Target != nullptr)
	{
		Target->Release();
	}
}

void d3d::EndFrame()
{
	Swap->Present(0, 0);
}

void d3d::InitializeDevice()
{
	HRESULT HR = S_OK;

	DXGI_SWAP_CHAIN_DESC DeviceDescription = {};

	DeviceDescription.BufferCount = 1;
	DeviceDescription.BufferDesc.Width = BufferWidth;
	DeviceDescription.BufferDesc.Height = BufferHeight;
	DeviceDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DeviceDescription.BufferDesc.RefreshRate.Numerator = 60;
	DeviceDescription.BufferDesc.RefreshRate.Denominator = 1;
	DeviceDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	DeviceDescription.OutputWindow = WindowHandle;
	DeviceDescription.SampleDesc.Count = 1;
	DeviceDescription.SampleDesc.Quality = 0;
	DeviceDescription.Windowed = TRUE;

	HR = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&DeviceDescription,
		&Swap,
		&Device,
		nullptr,
		&Context
	);

	D3D_ERROR_CHECK(HR);

	ID3D11Texture2D *BackFrameBuffer;

	Swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&BackFrameBuffer);

	HR = Device->CreateRenderTargetView(BackFrameBuffer, nullptr, &Target);

	D3D_ERROR_CHECK(HR);

	BackFrameBuffer->Release();
}