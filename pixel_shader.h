#pragma once

#include "common.h"
#include "direct3d.h"

#include <vector>

class pixel_shader
{
	private:

	ID3DBlob *Blob;
	ID3D11PixelShader *PixelShader;
	ID3D11InputLayout *InputLayout;

	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	public:

	pixel_shader(const wchar_t *File);
	~pixel_shader();

	void Bind();
};