#include "drawable_cars.h"

drawable_cars::drawable_cars(mesh *Asset, uint32 InstanceCount) :
	Asset(Asset),
	InstanceCount(InstanceCount)
{
	Instance.reserve(MAX_INSTANCES);
	//Instance = new drawable_cars_instance[MAX_INSTANCES];

	VertexShader = new vertex_shader(L"cars_instanced_vs.cso");
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

	PixelShader = new pixel_shader(L"cars_instanced_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Static);

	IndexBuffer = new index_buffer(Asset->GetIndices().data(), sizeof(uint32), Asset->GetIndexCount());

	InstanceBuffer = new instance_buffer(Instance.data(), sizeof(drawable_cars_instance), MAX_INSTANCES);

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	cbuffer_light PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void drawable_cars::Draw()
{
	cbuffer_input VertexShaderInput;

	VertexShaderInput.ViewProjection = XMMATRIX(camera::GetViewMatrix()) * XMMATRIX(camera::GetProjectionMatrix());

	cbuffer_light &PixelShaderInput = light_source::GetConstantBuffer();

	InstanceBuffer->UpdateDynamicBuffer(Instance.data());

	IndexBuffer->Bind();
	InstanceBuffer->Bind(VertexBuffer);

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&PixelShaderInput);

	//direct3d::GetContext()->RSSetState(RSCullNone);

	direct3d::GetContext()->DrawIndexedInstanced(IndexBuffer->GetSize(), Instance.size(), 0, 0, 0);

	Instance.clear();
}

void drawable_cars::PushInstance(XMMATRIX &Model, vec4 &Color)
{
	this->Instance.push_back({Model, Color});
}