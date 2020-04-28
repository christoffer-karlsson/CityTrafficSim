/*
==========================================================
	Buffer storing indicies to get loaded by gpu.
	Make sure to use indexed drawing.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

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