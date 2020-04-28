/*
==========================================================
	Create the pixel shader.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

class pixel_shader
{
	private:

	ID3DBlob			*Blob;
	ID3D11PixelShader	*PixelShader;

	public:

	pixel_shader(const wchar_t *File);
	~pixel_shader();

	void Bind();
};