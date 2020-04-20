#pragma once

#include "common.h"
#include "direct3d.h"
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