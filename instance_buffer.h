/*
==========================================================
	Create buffer with instanced geometry.
	When using instanced rendering, don't bind the
	vertex buffer. Bind the instance buffer with a
	pointer to the vertex buffer.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"
#include "vertex_buffer.h"

class instance_buffer
{
	private:

	ID3D11Buffer *Buffer;
	uint32		 Stride;
	uint32		 Size;

	public:

	instance_buffer(void *Data, uint32 Stride, uint32 Size);
	~instance_buffer();

	void Bind(vertex_buffer *VertexBuffer);
	void UpdateDynamicBuffer(void *Data);

	uint32 GetStride() const;
	uint32 GetSize() const;

	ID3D11Buffer *GetBuffer() const;
};