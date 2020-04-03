// d3d_shader.h: vertex and pixel shader interface

#pragma once

#include "common.h"
#include "diagnostics.h"
#include "global_device_info.h"
#include "external\WICTextureLoader.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>

class shader
{
	private:

	ID3DBlob			*Blob;
	ID3D11VertexShader	*VertexShader;
	ID3D11PixelShader	*PixelShader;
	ID3D11InputLayout	*InputLayout;

	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	public:

	shader(const wchar_t *VertexShaderFile, const wchar_t *PixelShaderFile);
	~shader();

	void AddInputElement(LPCSTR SemanticName, DXGI_FORMAT Format);
	void CommitInputElements();

	void Bind();
};