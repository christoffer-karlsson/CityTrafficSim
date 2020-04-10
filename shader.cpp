#include "shader.h"

shader::shader(const wchar_t *VertexShaderFile, const wchar_t *PixelShaderFile) :
	Blob(nullptr), 
	VertexShader(nullptr),
	PixelShader(nullptr),
	InputLayout(nullptr),
	Layout()
{
	HRESULT HR = S_OK;

	HR = D3DReadFileToBlob(PixelShaderFile, &Blob);
	D3D_ERROR_CHECK(HR);

	HR = global_device_info::Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader);
	D3D_ERROR_CHECK(HR);

	HR = D3DReadFileToBlob(VertexShaderFile, &Blob);
	D3D_ERROR_CHECK(HR);

	HR = global_device_info::Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader);
	D3D_ERROR_CHECK(HR);
}

void shader::AddInputElement(LPCSTR SemanticName, DXGI_FORMAT Format)
{
	Layout.push_back({ SemanticName, 0, Format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
}

void shader::CommitInputElements()
{
	HRESULT HR = S_OK;

	HR = global_device_info::Device->CreateInputLayout(Layout.data(), (uint32)Layout.size(), Blob->GetBufferPointer(), Blob->GetBufferSize(), &InputLayout);
}

void shader::Bind()
{
	global_device_info::Context->PSSetShader(PixelShader, nullptr, 0);
	global_device_info::Context->VSSetShader(VertexShader, nullptr, 0);
	global_device_info::Context->IASetInputLayout(InputLayout);
}

shader::~shader()
{
	if(Blob != nullptr)
	{
		Blob->Release();
	}

	if(VertexShader != nullptr)
	{
		VertexShader->Release();
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