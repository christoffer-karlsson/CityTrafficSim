#pragma once

#include "common.h"
#include "direct3d.h"

// NOTE(Cristoffer): Allows to create a dynamic of static buffer.
// If dynamic buffer is instantiated, then use the function to update
// the vertex buffer on demand.

enum class accessibility
{
	Dynamic,
	Static,
};

class vertex_buffer
{
	private:

	ID3D11Buffer *Buffer;
	uint32		 Stride;
	uint32		 Size;

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