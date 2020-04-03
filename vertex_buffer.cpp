#include "vertex_buffer.h"

vertex_buffer::vertex_buffer(void *Vertices, uint32 Stride, uint32 Size) :
	VertexBuffer(nullptr), 
	IndexBuffer(nullptr),
	VertexBufferStride(Stride), 
	VertexBufferSize(Size),
	IndexBufferStride(0), 
	IndexBufferSize(0)
{
	HRESULT HR = S_OK;

	D3D11_BUFFER_DESC BufferDesc = {};
	BufferDesc.StructureByteStride = Stride;
	BufferDesc.ByteWidth = Size * Stride;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = Vertices;

	HR = global_device_info::Device->CreateBuffer(&BufferDesc, &SubResourceData, &VertexBuffer);
	D3D_ERROR_CHECK(HR);
}

void vertex_buffer::AddIndexBuffer(void *Indices, uint32 Stride, uint32 Size)
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
	SubResourceData.pSysMem = Indices;

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