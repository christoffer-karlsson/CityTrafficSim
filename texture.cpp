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

	HR = CreateWICTextureFromFile(direct3d::GetDevice(), direct3d::GetContext(), Filename, nullptr, &TextureView);
	D3D_ERROR_CHECK(HR);

	D3D11_SAMPLER_DESC SamplerDesc = {};
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HR = direct3d::GetDevice()->CreateSamplerState(&SamplerDesc, &Sampler);
	D3D_ERROR_CHECK(HR);
}

void texture::Bind()
{
	direct3d::GetContext()->PSSetShaderResources(0, 1, &TextureView);
	direct3d::GetContext()->PSSetSamplers(0, 1, &Sampler);
}

uv_quad texture::GetUVFromSliceCoordinates(int32 X, int32 Y)
{
	uv_quad Result;
	
	Result.TextureCoordinate[0] = { (0.0f + X) / (real32)SlicesInX, (0.0f + Y) / (real32)SlicesInY };
	Result.TextureCoordinate[1] = { (1.0f + X) / (real32)SlicesInX, (0.0f + Y) / (real32)SlicesInY };
	Result.TextureCoordinate[2] = { (0.0f + X) / (real32)SlicesInX, (1.0f + Y) / (real32)SlicesInY };
	Result.TextureCoordinate[3] = { (1.0f + X) / (real32)SlicesInX, (1.0f + Y) / (real32)SlicesInY };

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