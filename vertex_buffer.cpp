#include "vertex_buffer.h"

vertex_buffer::vertex_buffer(void *VertexData, uint32 Stride, uint32 Size, accessibility CPUAccess) :
	Buffer(nullptr), 
	Stride(Stride), 
	Size(Size),
	CPUAccess(CPUAccess)
{
	HRESULT HR = S_OK;

	D3D11_BUFFER_DESC BufferDesc = {};
	// NOTE(Cristoffer): ByteWidth: Total buffer size in bytes.
	BufferDesc.ByteWidth = Size * Stride;
	// NOTE(Cristoffer): StructureByteStride: Size of each element in bytes.
	BufferDesc.StructureByteStride = Stride;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	if(CPUAccess == accessibility::Dynamic)
	{
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	}

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = VertexData;
	SubResourceData.SysMemPitch = 0;
	SubResourceData.SysMemSlicePitch = 0;

	HR = d3d_api::GetDevice()->CreateBuffer(&BufferDesc, &SubResourceData, &Buffer);
	D3D_ERROR_CHECK(HR);
}

void vertex_buffer::Bind()
{
	uint32 Offset = 0;

	d3d_api::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);
}

void vertex_buffer::UpdateDynamicBuffer(void *Data, uint32 Stride, uint32 Size)
{
	// TODO(Cristoffer): Need better structure so that objects that didn't declare
	// dynamic buffer could not access this method. Assertion for now.

	assert(CPUAccess == accessibility::Dynamic);

	D3D11_MAPPED_SUBRESOURCE Resource;

	d3d_api::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);

	memcpy(Resource.pData, Data, (size_t)Stride * (size_t)Size);

	d3d_api::GetContext()->Unmap(Buffer, 0);
}

uint32 vertex_buffer::GetSize() const
{
	return Size;
}

uint32 vertex_buffer::GetStride() const
{
	return Stride;
}

ID3D11Buffer *vertex_buffer::GetBuffer() const
{
	return Buffer;
}

vertex_buffer::~vertex_buffer()
{
	if(Buffer != nullptr)
	{
		Buffer->Release();
	}
}