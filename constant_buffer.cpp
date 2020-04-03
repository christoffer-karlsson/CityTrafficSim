#include "constant_buffer.h"

constant_buffer::constant_buffer(void *ShaderInput, uint32 Size) :
	ConstantBuffer(nullptr), 
	Size(Size)
{
	HRESULT HR = S_OK;

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;
	BufferDesc.ByteWidth = Size;
	BufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = ShaderInput;

	HR = global_device_info::Device->CreateBuffer(&BufferDesc, &SubResourceData, &ConstantBuffer);
	D3D_ERROR_CHECK(HR);
}

void constant_buffer::Update(void *ShaderInput)
{
	D3D11_MAPPED_SUBRESOURCE MappedSubResource;

	global_device_info::Context->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedSubResource);

	memcpy(MappedSubResource.pData, ShaderInput, Size);

	global_device_info::Context->Unmap(ConstantBuffer, 0);
}

void constant_buffer::Bind()
{
	global_device_info::Context->VSSetConstantBuffers(0, 1, &ConstantBuffer);
}

constant_buffer::~constant_buffer()
{
	if(ConstantBuffer != nullptr)
	{
		ConstantBuffer->Release();
	}
}