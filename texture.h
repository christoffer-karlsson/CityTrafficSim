// d3d_texture.h: d3d texture interface

#pragma once

#include "common.h"
#include "direct3d.h"
#include "external/WICTextureLoader.h"

using namespace DirectX;

// NOTE(Cristoffer): Only supports sampling for evenly spaced
// texture atlas for now.

// TODO(Cristoffer): Add support for texture slots.

struct uv;
struct uv_quad;

class texture
{
	private:

	ID3D11ShaderResourceView	*TextureView;
	ID3D11SamplerState			*Sampler;

	int32 AtlasWidth;
	int32 AtlasHeight;
	int32 SlicesInX;
	int32 SlicesInY;

	const wchar_t *Filename;

	public:

	texture(const wchar_t *Filename, int32 Width, int32 Height, int32 SlicesX, int32 SlicesY);
	~texture();

	void Bind();
	uv_quad GetUVFromSliceCoordinates(int32 X, int32 Y);
};

struct uv
{
	real32 U, V;
};

struct uv_quad
{
	uv TextureCoordinate[4];
};