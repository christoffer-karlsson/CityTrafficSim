// d3d_texture.h: d3d texture interface

#pragma once

#include "common.h"
#include "direct3d.h"
#include "external/WICTextureLoader.h"

using namespace DirectX;

// NOTE(Cristoffer): Only supports sampling for evenly spaced
// texture atlas for now.

// TODO(Cristoffer): Add support for texture slots.

struct texture_coordinates
{
	vec2 TopLeft;
	vec2 TopRight;
	vec2 BottomLeft;
	vec2 BottomRight;
};

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

	texture_coordinates GetUVFromSliceCoordinates(int32 X, int32 Y);
};