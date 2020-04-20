// d3d_shader.h: vertex and pixel shader interface

#pragma once

#include "common.h"
#include "direct3d.h"

#include <vector>

#define MAX_INPUT_SLOTS 15

class vertex_shader
{
	private:

	ID3DBlob			*Blob;
	ID3D11VertexShader	*VertexShader;
	ID3D11InputLayout	*InputLayout;

	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	uint32 ByteOffset[MAX_INPUT_SLOTS];

	public:

	vertex_shader(const wchar_t *File);
	~vertex_shader();

	void AddInputElement(uint32 Slot, LPCSTR SemanticName, DXGI_FORMAT Format, D3D11_INPUT_CLASSIFICATION Class = D3D11_INPUT_PER_VERTEX_DATA, uint32 SemanticIndex = 0);
	void CommitInputElements();

	void Bind();
};