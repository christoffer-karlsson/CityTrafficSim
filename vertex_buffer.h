#pragma once

#include "common.h"
#include "diagnostics.h"
#include "global_device_info.h"

#include <d3d11.h>

class vertex_buffer
{
	private:

	ID3D11Buffer	*VertexBuffer;
	uint32			VertexBufferStride;
	uint32			VertexBufferSize;

	ID3D11Buffer	*IndexBuffer;
	uint32			IndexBufferStride;
	uint32			IndexBufferSize;

	public:

	vertex_buffer(void *Vertices, uint32 Stride, uint32 Size);
	~vertex_buffer();

	void AddIndexBuffer(void *Indices, uint32 Stride, uint32 Size);

	void Bind();

	uint32 GetVertexCount() const;
	uint32 GetIndexCount() const;
};
