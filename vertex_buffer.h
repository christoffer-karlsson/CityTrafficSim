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

	ID3D11Buffer	*VertexBuffer;
	uint32			VertexBufferStride;
	uint32			VertexBufferSize;

	ID3D11Buffer	*IndexBuffer;
	uint32			IndexBufferStride;
	uint32			IndexBufferSize;

	accessibility	CPUAccess;

	public:

	vertex_buffer(void *VertexData, uint32 Stride, uint32 Size, accessibility CPUAccess);
	~vertex_buffer();

	void AddIndexBuffer(void *IndicesData, uint32 Stride, uint32 Size);

	void Bind();
	void UpdateDynamicBuffer(void *VertexData, uint32 Stride, uint32 Size);

	uint32 GetVertexCount() const;
	uint32 GetIndexCount() const;
};
