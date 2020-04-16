#include "pixel_shader.h"

pixel_shader::pixel_shader(const wchar_t *File) :
	Blob(nullptr),
	PixelShader(nullptr),
	InputLayout(nullptr),
	Layout()
{
	HRESULT HR = S_OK;

	HR = D3DReadFileToBlob(File, &Blob);
	D3D_ERROR_CHECK(HR);

	HR = direct3d::GetDevice()->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader);
	D3D_ERROR_CHECK(HR);
}

void pixel_shader::Bind()
{
	direct3d::GetContext()->PSSetShader(PixelShader, nullptr, 0);;
}

pixel_shader::~pixel_shader()
{
	if(Blob != nullptr)
	{
		Blob->Release();
	}

	if(PixelShader != nullptr)
	{
		PixelShader->Release();
	}

	if(InputLayout != nullptr)
	{
		InputLayout->Release();
	}
}