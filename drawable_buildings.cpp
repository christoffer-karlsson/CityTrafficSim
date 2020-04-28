#include "drawable_buildings.h"

drawable_buildings::drawable_buildings(mesh *Asset) :
	Asset(Asset)
{
	Instance.reserve(MAX_INSTANCES);

	VertexShader = new vertex_shader(L"instanced_object_vs.cso");
	VertexShader->AddInputElement(0, "POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "TEXCOORD", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement(0, "HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);

	// NOTE(Cristoffer): Instanced vertex shader input.
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 0);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 2);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 3);
	VertexShader->AddInputElement(1, "INSTANCE_COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA);
	
	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"instanced_object_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Static);

	InstanceBuffer = new instance_buffer(Instance.data(), sizeof(instance_vs), MAX_INSTANCES);

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	light_point PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void drawable_buildings::Draw()
{
	cbuffer_input VertexShaderInput;
	VertexShaderInput.ViewProjection = XMMATRIX(ActiveCamera->GetViewMatrix()) * XMMATRIX(ActiveCamera->GetProjectionMatrix());

	InstanceBuffer->UpdateDynamicBuffer(Instance.data());
	InstanceBuffer->Bind(VertexBuffer);

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&WorldLight);

	d3d_api::GetContext()->DrawInstanced(VertexBuffer->GetSize(), Instance.size(), 0, 0);
}

void drawable_buildings::PushInstance(XMMATRIX &Model, vec4 &Color)
{
	this->Instance.push_back({ Model, Color });
}

void drawable_buildings::ClearInstances()
{
	Instance.clear();
}
