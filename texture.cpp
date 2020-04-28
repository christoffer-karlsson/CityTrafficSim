#include "texture.h"

texture::texture(const wchar_t *Filename, int32 AtlasWidth, int32 AtlasHeight, int32 SlicesInX, int32 SlicesInY) :
	TextureView(nullptr), 
	Sampler(nullptr),
	Filename(Filename),
	AtlasWidth(AtlasWidth),
	AtlasHeight(AtlasHeight),
	SlicesInX(SlicesInX),
	SlicesInY(SlicesInY)
{
	HRESULT HR = S_OK;

	HR = CreateWICTextureFromFile(d3d_api::GetDevice(), d3d_api::GetContext(), Filename, nullptr, &TextureView);
	D3D_ERROR_CHECK(HR);

	D3D11_SAMPLER_DESC SamplerDesc = {};
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HR = d3d_api::GetDevice()->CreateSamplerState(&SamplerDesc, &Sampler);
	D3D_ERROR_CHECK(HR);
}

void texture::Bind()
{
	d3d_api::GetContext()->PSSetShaderResources(0, 1, &TextureView);
	d3d_api::GetContext()->PSSetSamplers(0, 1, &Sampler);
}

texture_coordinates texture::GetUVFromSliceCoordinates(int32 X, int32 Y)
{
	texture_coordinates Result;
	
	Result.TopLeft	= { (0.0f + X) / (real32)SlicesInX, (0.0f + Y) / (real32)SlicesInY };
	Result.TopRight = { (1.0f + X) / (real32)SlicesInX, (0.0f + Y) / (real32)SlicesInY };
	Result.BottomLeft = { (0.0f + X) / (real32)SlicesInX, (1.0f + Y) / (real32)SlicesInY };
	Result.BottomRight = { (1.0f + X) / (real32)SlicesInX, (1.0f + Y) / (real32)SlicesInY };

	return Result;
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