/*
==========================================================
	Create a dynamic or static vertex buffer.
	If dynamic buffer is created, make sure to do
	dynamic update every frame before calling draw.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

enum class accessibility
{
	Dynamic,
	Static,
};

class vertex_buffer
{
	private:

	ID3D11Buffer	*Buffer;
	uint32			Stride;
	uint32			Size;

	accessibility	CPUAccess;

	public:

	vertex_buffer(void *Data, uint32 Stride, uint32 Size, accessibility CPUAccess);
	~vertex_buffer();

	void Bind();
	void UpdateDynamicBuffer(void *Data, uint32 Stride, uint32 Size);

	uint32 GetStride() const;
	uint32 GetSize() const;

	ID3D11Buffer *GetBuffer() const;
};