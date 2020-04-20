#pragma once

#include "common.h"
#include "direct3d.h"

class index_buffer
{
	private:

	ID3D11Buffer *Buffer;
	uint32		 Stride;
	uint32		 Size;

	public:

	index_buffer(void *Data, uint32 Stride, uint32 Size);
	~index_buffer();

	void Bind();

	uint32 GetStride() const;
	uint32 GetSize() const;
};