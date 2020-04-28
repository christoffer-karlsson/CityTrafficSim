#include "drawable_cars.h"

drawable_cars::drawable_cars(mesh *Asset) :
	Asset(Asset)
{
	Instance.reserve(MAX_INSTANCES);

	VertexShader = new vertex_shader(L"instanced_object_dir_light_vs.cso");
	VertexShader->AddInputElement(0, "POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "TEXCOORD", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement(0, "COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement(0, "HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);

	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 0);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 2);
	VertexShader->AddInputElement(1, "INSTANCE_MODEL_MATRIX", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA, 3);
	VertexShader->AddInputElement(1, "INSTANCE_COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_INPUT_PER_INSTANCE_DATA);

	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"instanced_object_dir_light_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Static);

	IndexBuffer = new index_buffer(Asset->GetIndices().data(), sizeof(uint32), Asset->GetIndexCount());

	InstanceBuffer = new instance_buffer(Instance.data(), sizeof(instance_vs), MAX_INSTANCES);

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	light_directional PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void drawable_cars::Draw()
{
	light_directional PixelShaderInput;
	PixelShaderInput.Direction = XMFLOAT3(0.0f, 1.0f, 0.5f);
	PixelShaderInput.Ambient = XMFLOAT4(0.50f, 0.61f, 0.83f, 1.0f);
	PixelShaderInput.Diffuse = XMFLOAT4(0.87f, 0.81f, 0.78f, 1.0f);

	cbuffer_input VertexShaderInput;
	VertexShaderInput.ViewProjection = XMMATRIX(ActiveCamera->GetViewMatrix()) * XMMATRIX(ActiveCamera->GetProjectionMatrix());

	InstanceBuffer->UpdateDynamicBuffer(Instance.data());

	IndexBuffer->Bind();
	InstanceBuffer->Bind(VertexBuffer);

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&PixelShaderInput);

	d3d_api::GetContext()->DrawIndexedInstanced(IndexBuffer->GetSize(), Instance.size(), 0, 0, 0);

	Instance.clear();
}

void drawable_cars::PushInstance(XMMATRIX &Model, vec4 &Color)
{
	this->Instance.push_back({Model, Color});
}