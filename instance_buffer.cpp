#include "instance_buffer.h"

instance_buffer::instance_buffer(void *Data, uint32 Stride, uint32 Size) :
	Buffer(nullptr),
	Stride(Stride),
	Size(Size)
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

	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = Data;
	SubResourceData.SysMemPitch = 0;
	SubResourceData.SysMemSlicePitch = 0;

	HR = d3d_api::GetDevice()->CreateBuffer(&BufferDesc, &SubResourceData, &Buffer);
	D3D_ERROR_CHECK(HR);
}

void instance_buffer::Bind(vertex_buffer *VertexBuffer)
{
	// NOTE(Cristoffer): Set up instance buffer together with vertex buffer.
	uint32 Offsets[2];
	Offsets[0] = 0;
	Offsets[1] = 0;

	uint32 Strides[2];
	Strides[0] = VertexBuffer->GetStride();
	Strides[1] = Stride;

	ID3D11Buffer *BufferPointers[2];
	BufferPointers[0] = VertexBuffer->GetBuffer();
	BufferPointers[1] = Buffer;

	d3d_api::GetContext()->IASetVertexBuffers(0, 2, BufferPointers, Strides, Offsets);
}

void instance_buffer::UpdateDynamicBuffer(void *Data)
{
	D3D11_MAPPED_SUBRESOURCE Resource;

	d3d_api::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);

	memcpy(Resource.pData, Data, (size_t)Stride * (size_t)Size);

	d3d_api::GetContext()->Unmap(Buffer, 0);
}

uint32 instance_buffer::GetStride() const
{
	return Stride;
}

uint32 instance_buffer::GetSize() const
{
	return Size;
}

ID3D11Buffer *instance_buffer::GetBuffer() const
{
	return Buffer;
}

instance_buffer::~instance_buffer()
{
	if(Buffer != nullptr)
	{
		Buffer->Release();
	}
}