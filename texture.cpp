#include "texture.h"

texture::texture(const wchar_t *Filename, int32 Width, int32 Height, int32 SlicesX, int32 SlicesY) :
	TextureView(nullptr), 
	Sampler(nullptr),
	Filename(Filename),
	Width(0), 
	Height(0), 
	SlicesX(0), 
	SlicesY(0)
{
	HRESULT HR = S_OK;

	HR = CreateWICTextureFromFile(global_device_info::Device, global_device_info::Context, Filename, nullptr, &TextureView);
	D3D_ERROR_CHECK(HR);

	D3D11_SAMPLER_DESC SamplerDesc = {};
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HR = global_device_info::Device->CreateSamplerState(&SamplerDesc, &Sampler);
	D3D_ERROR_CHECK(HR);
}

void texture::Bind()
{
	global_device_info::Context->PSSetShaderResources(0, 1, &TextureView);
	global_device_info::Context->PSSetSamplers(0, 1, &Sampler);
}

texture::~texture()
{
	if(TextureView != nullptr)
	{
		TextureView->Release();
	}

	if(Sampler != nullptr)
	{
		Sampler->Release();
	}
}