#include "index_buffer.h"

index_buffer::index_buffer(void *Data, uint32 Stride, uint32 Size) :
	Buffer(nullptr),
	Stride(Stride),
	Size(Size)
{
	HRESULT HR = S_OK;

	D3D11_BUFFER_DESC BufferDesc = {};
	BufferDesc.StructureByteStride = Stride;
	BufferDesc.ByteWidth = Size * Stride;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = Data;

	HR = direct3d::GetDevice()->CreateBuffer(&BufferDesc, &SubResourceData, &Buffer);
	D3D_ERROR_CHECK(HR);
}

void index_buffer::Bind()
{
	direct3d::GetContext()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}

uint32 index_buffer::GetSize() const
{
	return Size;
}

uint32 index_buffer::GetStride() const
{
	return Stride;
}

index_buffer::~index_buffer()
{
	if(Buffer != nullptr)
	{
		Buffer->Release();
	}
}