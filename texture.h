/*
==========================================================
	Load texture from image file.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"
#include "external/WICTextureLoader.h"

// TODO(Cristoffer): Add support for texture slots.
// TODO(Cristoffer): Pull out the file loading to asset manager.
// TODO(Cristoffer): Implement a specific texture type for tile grid.

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