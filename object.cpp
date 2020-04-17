#include "object.h"

object::object(model *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color) :
	Asset(Asset)
{
	SetInitialModel(Position, Scale, Rotation);

	VertexShader = new vertex_shader(L"vehicle_vs.cso");
	VertexShader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement("HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"vehicle_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Dynamic);
	VertexBuffer->AddIndexBuffer(Asset->GetIndices().data(), sizeof(uint32), Asset->GetIndexCount());

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	cbuffer_light PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void object::Draw()
{
	cbuffer_input VertexShaderInput;

	VertexShaderInput.MVP = XMMatrixTranspose(Model * XMMATRIX(camera::GetViewMatrix()) * XMMATRIX(camera::GetProjectionMatrix()));
	VertexShaderInput.Model = XMMatrixTranspose(Model);

	cbuffer_light &PixelShaderInput = light_source::GetConstantBuffer();

	VertexBuffer->Bind();
	VertexShader->Bind();

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&PixelShaderInput);

	direct3d::GetContext()->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}