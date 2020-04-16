#include "vertex_shader.h"

vertex_shader::vertex_shader(const wchar_t *File) :
	Blob(nullptr), 
	VertexShader(nullptr),
	InputLayout(nullptr),
	Layout()
{
	HRESULT HR = S_OK;

	HR = D3DReadFileToBlob(File, &Blob);
	D3D_ERROR_CHECK(HR);

	HR = direct3d::GetDevice()->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader);
	D3D_ERROR_CHECK(HR);
}

void vertex_shader::AddInputElement(LPCSTR SemanticName, DXGI_FORMAT Format)
{
	Layout.push_back({ SemanticName, 0, Format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
}

void vertex_shader::CommitInputElements()
{
	HRESULT HR = S_OK;

	HR = direct3d::GetDevice()->CreateInputLayout(Layout.data(), (uint32)Layout.size(), Blob->GetBufferPointer(), Blob->GetBufferSize(), &InputLayout);
}

void vertex_shader::Bind()
{
	direct3d::GetContext()->VSSetShader(VertexShader, nullptr, 0);
	direct3d::GetContext()->IASetInputLayout(InputLayout);
}

vertex_shader::~vertex_shader()
{
	if(Blob != nullptr)
	{
		Blob->Release();
	}

	if(VertexShader != nullptr)
	{
		VertexShader->Release();
	}

	if(InputLayout != nullptr)
	{
		InputLayout->Release();
	}
}