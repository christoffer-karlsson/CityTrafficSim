#include "drawable_object.h"

drawable_object::drawable_object(mesh *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color) :
	Asset(Asset)
{
	VertexShader = new vertex_shader(L"object_vs.cso");
	VertexShader->AddInputElement(0, "POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "TEXCOORD", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement(0, "HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"object_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Static);
	IndexBuffer = new index_buffer(Asset->GetIndices().data(), sizeof(uint32), Asset->GetIndexCount());

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	light_point PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void drawable_object::Draw()
{
	cbuffer_input VertexShaderInput;

	VertexShaderInput.MVP = XMMatrixTranspose(
		GetWorldModel().GetMatrix() * 
		XMMATRIX(ActiveCamera->GetViewMatrix()) *
		XMMATRIX(ActiveCamera->GetProjectionMatrix()));

	VertexShaderInput.Model = XMMatrixTranspose(GetWorldModel().GetMatrix());

	VertexBuffer->Bind();
	IndexBuffer->Bind();

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&WorldLight);

	d3d_api::GetContext()->DrawIndexed(IndexBuffer->GetSize(), 0, 0);
}

drawable_object::~drawable_object()
{
}
