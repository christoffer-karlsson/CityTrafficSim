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

	HR = d3d_api::GetDevice()->CreateBuffer(&BufferDesc, nullptr, &ConstantBuffer);
	D3D_ERROR_CHECK(HR);
}

void constant_buffer::Update(void *ShaderInput)
{
	D3D11_MAPPED_SUBRESOURCE MappedSubResource;

	d3d_api::GetContext()->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedSubResource);

	memcpy(MappedSubResource.pData, ShaderInput, Size);

	d3d_api::GetContext()->Unmap(ConstantBuffer, 0);
}

void constant_buffer::Bind(uint32 Slot, shader_set_type ShaderType)
{
	if(ShaderType == shader_set_type::SetVertexShader)
	{
		d3d_api::GetContext()->VSSetConstantBuffers(Slot, 1, &ConstantBuffer);
	}

	if(ShaderType == shader_set_type::SetPixelShader)
	{
		d3d_api::GetContext()->PSSetConstantBuffers(Slot, 1, &ConstantBuffer);
	}
}

constant_buffer::~constant_buffer()
{
	if(ConstantBuffer != nullptr)
	{
		ConstantBuffer->Release();
	}
}