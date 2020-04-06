#include "vertex_buffer.h"

vertex_buffer::vertex_buffer(void *VertexData, uint32 Stride, uint32 Size, ACCESSIBILITY CPUAccess) :
	VertexBuffer(nullptr), 
	IndexBuffer(nullptr),
	VertexBufferStride(Stride), 
	VertexBufferSize(Size),
	IndexBufferStride(0), 
	IndexBufferSize(0),
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

	if(CPUAccess == DYNAMIC)
	{
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	}

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = VertexData;
	SubResourceData.SysMemPitch = 0;
	SubResourceData.SysMemSlicePitch = 0;

	HR = global_device_info::Device->CreateBuffer(&BufferDesc, &SubResourceData, &VertexBuffer);
	D3D_ERROR_CHECK(HR);
}

void vertex_buffer::AddIndexBuffer(void *IndicesData, uint32 Stride, uint32 Size)
{
	HRESULT HR = S_OK;

	IndexBufferSize = Size;

	D3D11_BUFFER_DESC BufferDesc = {};
	BufferDesc.StructureByteStride = Stride;
	BufferDesc.ByteWidth = Size * Stride;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = IndicesData;

	HR = global_device_info::Device->CreateBuffer(&BufferDesc, &SubResourceData, &IndexBuffer);
	D3D_ERROR_CHECK(HR);
}

void vertex_buffer::Bind()
{
	uint32 Offset = 0;

	global_device_info::Context->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexBufferStride, &Offset);

	if(IndexBufferSize > 0)
	{
		global_device_info::Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	}
}

void vertex_buffer::UpdateDynamicBuffer(void *VertexData, uint32 Stride, uint32 Size)
{
	// NOTE(Cristoffer): Need better structure so that objects that didn't declare
	// dynamic buffer could not access this method. Assertion for now.

	assert(CPUAccess == DYNAMIC);

	D3D11_MAPPED_SUBRESOURCE Resource;

	global_device_info::Context->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);

	memcpy(Resource.pData, VertexData, Stride * Size);

	global_device_info::Context->Unmap(VertexBuffer, 0);
}

uint32 vertex_buffer::GetVertexCount() const
{
	return VertexBufferSize;
}

uint32 vertex_buffer::GetIndexCount() const
{
	return IndexBufferSize;
}

vertex_buffer::~vertex_buffer()
{
	if(VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
	}

	if(IndexBuffer != nullptr)
	{
		IndexBuffer->Release();
	}
}