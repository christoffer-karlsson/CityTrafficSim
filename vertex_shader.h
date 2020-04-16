// d3d_shader.h: vertex and pixel shader interface

#pragma once

#include "common.h"
#include "direct3d.h"

#include <vector>

class vertex_shader
{
	private:

	ID3DBlob			*Blob;
	ID3D11VertexShader	*VertexShader;
	ID3D11InputLayout	*InputLayout;

	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	public:

	vertex_shader(const wchar_t *File);
	~vertex_shader();

	void AddInputElement(LPCSTR SemanticName, DXGI_FORMAT Format);
	void CommitInputElements();

	void Bind();
};