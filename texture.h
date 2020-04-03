// d3d_texture.h: d3d texture interface

#pragma once

#include "common.h"

#include "diagnostics.h"
#include "global_device_info.h"
#include "external/WICTextureLoader.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

// NOTE(Cristoffer): Only supports sampling for evenly spaced
// texture atlas for now.

class texture
{
	private:

	ID3D11ShaderResourceView	*TextureView;
	ID3D11SamplerState			*Sampler;

	int32 Width;
	int32 Height;

	int32 SlicesX;
	int32 SlicesY;

	const wchar_t *Filename;

	public:

	texture(const wchar_t *Filename, int32 Width, int32 Height, int32 SlicesX, int32 SlicesY);
	~texture();

	void Bind();
};