/*
==========================================================
	Create the vertex shader with a defined
	input layout that matches the per vertex input
	data structure.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

#include <vector>

// Maximum input slots that are defined by the api.
#define MAX_INPUT_SLOTS 15

class vertex_shader
{
	private:

	ID3DBlob			*Blob;
	ID3D11VertexShader	*VertexShader;
	ID3D11InputLayout	*InputLayout;
	uint32				ByteOffset[MAX_INPUT_SLOTS];

	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	public:

	vertex_shader(const wchar_t *File);
	~vertex_shader();

	void AddInputElement(uint32 Slot, LPCSTR SemanticName, DXGI_FORMAT Format, D3D11_INPUT_CLASSIFICATION Class = D3D11_INPUT_PER_VERTEX_DATA, uint32 SemanticIndex = 0);
	void CommitInputElements();

	void Bind();
};