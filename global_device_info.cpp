#include "global_device_info.h"

int32 global_device_info::WindowWidth = 0;
int32 global_device_info::WindowHeight = 0;

real32 const global_device_info::FrameBufferWidth = 1920.0f;
real32 const global_device_info::FrameBufferHeight = 1080.0f;

//real32 const global_device_info::FrameBufferWidth = 1280.0f;
//real32 const global_device_info::FrameBufferHeight = 720.0f;

IDXGISwapChain			*global_device_info::Swap = nullptr;
ID3D11Device			*global_device_info::Device = nullptr;
ID3D11DeviceContext		*global_device_info::Context = nullptr;
ID3D11RenderTargetView	*global_device_info::Target = nullptr;