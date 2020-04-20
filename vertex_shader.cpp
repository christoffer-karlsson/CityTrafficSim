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

	for(uint32 Index = 0;
		Index < MAX_INPUT_SLOTS;
		Index++)
	{
		ByteOffset[Index] = 0;
	}
}

void vertex_shader::AddInputElement(uint32 Slot, LPCSTR SemanticName, DXGI_FORMAT Format, D3D11_INPUT_CLASSIFICATION Class, uint32 SemanticIndex)
{
	D3D11_INPUT_ELEMENT_DESC InputLayout;

	InputLayout.SemanticName = SemanticName;
	InputLayout.SemanticIndex = SemanticIndex;
	InputLayout.Format = Format;
	InputLayout.InputSlot = Slot;
	//InputLayout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	InputLayout.AlignedByteOffset = ByteOffset[Slot];
	InputLayout.InputSlotClass = Class;

	// NOTE(Cristoffer): Must be set to 0 if containing per vertex data (according to MSDN docs).
	if(Class == D3D11_INPUT_PER_INSTANCE_DATA)
	{
		InputLayout.InstanceDataStepRate = 1;
	}
	else
	{
		InputLayout.InstanceDataStepRate = 0;
	}

	Layout.push_back(InputLayout);

	// NOTE(Cristoffer): Add to the byte offset.
	switch(Format)
	{
		case DXGI_FORMAT_R32_FLOAT:				ByteOffset[Slot] += (1 * 4); break;
		case DXGI_FORMAT_R32G32_FLOAT:			ByteOffset[Slot] += (2 * 4); break;
		case DXGI_FORMAT_R32G32B32_FLOAT:		ByteOffset[Slot] += (3 * 4); break;
		case DXGI_FORMAT_R32G32B32A32_FLOAT:	ByteOffset[Slot] += (4 * 4); break;
		case DXGI_FORMAT_R32_UINT:				ByteOffset[Slot] += (1 * 4); break;
		case DXGI_FORMAT_R32G32_UINT:			ByteOffset[Slot] += (2 * 4); break;
		case DXGI_FORMAT_R32G32B32_UINT:		ByteOffset[Slot] += (3 * 4); break;
		case DXGI_FORMAT_R32G32B32A32_UINT:		ByteOffset[Slot] += (4 * 4); break;
		case DXGI_FORMAT_R32_SINT:				ByteOffset[Slot] += (1 * 4); break;
		case DXGI_FORMAT_R32G32_SINT:			ByteOffset[Slot] += (2 * 4); break;
		case DXGI_FORMAT_R32G32B32_SINT:		ByteOffset[Slot] += (3 * 4); break;
		case DXGI_FORMAT_R32G32B32A32_SINT:		ByteOffset[Slot] += (4 * 4); break;
	}
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