#include "drawable_cars.h"

drawable_cars::drawable_cars(mesh *Asset) :
	Asset(Asset)
{
	Instance.reserve(MAX_INSTANCES);

	VertexShader = new vertex_shader(L"instanced_object_vs.cso");
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

	PixelShader = new pixel_shader(L"instanced_object_ps.cso");

	VertexBuffer = new vertex_buffer(Asset->GetVertices().data(), sizeof(vertex), Asset->GetVertexCount(), accessibility::Static);

	IndexBuffer = new index_buffer(Asset->GetIndices().data(), sizeof(uint32), Asset->GetIndexCount());

	InstanceBuffer = new instance_buffer(Instance.data(), sizeof(instance_vs), MAX_INSTANCES);

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));

	cbuffer_light PixelShaderInput;
	ConstantBuffer[1] = new constant_buffer(&PixelShaderInput, sizeof(PixelShaderInput));
}

void drawable_cars::Draw()
{
	cbuffer_input VertexShaderInput;

	VertexShaderInput.ViewProjection = XMMATRIX(camera::GetViewMatrix()) * XMMATRIX(camera::GetProjectionMatrix());

	/*directional_light PixelShaderInput;
	PixelShaderInput.Direction = XMFLOAT3(0.1f, 0.6f, 0.1f);
	PixelShaderInput.Ambient = XMFLOAT4(0.35f, 0.35f, 0.35f, 1.0f);
	PixelShaderInput.Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);*/

	/*struct cbuffer_light
	{
		XMFLOAT3 LightPosition; alignas(16)
		XMFLOAT3 Ambient; alignas(16)
		XMFLOAT3 DiffuseColor; alignas(16)
		real32 DiffuseIntensity = 1.0f;
		real32 AttenuationConstant = 1.0f;
		real32 AttenuationLinear = 0.002f;
		real32 AttenuationQuad = 0.000007f;
	} PixelShaderInput;

	PixelShaderInput.LightPosition.x = 0.0f;
	PixelShaderInput.LightPosition.y = 100.0f;
	PixelShaderInput.LightPosition.z = 0.0f;

	PixelShaderInput.DiffuseColor.x = 0.9f;
	PixelShaderInput.DiffuseColor.y = 0.9f;
	PixelShaderInput.DiffuseColor.z = 0.9f;

	PixelShaderInput.Ambient.x = 0.50f;
	PixelShaderInput.Ambient.y = 0.61f;
	PixelShaderInput.Ambient.z = 0.83f;*/

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


	//direct3d::GetContext()->DrawInstanced(VertexBuffer->GetSize(), Instance.size(), 0, 0);
	direct3d::GetContext()->DrawIndexedInstanced(IndexBuffer->GetSize(), Instance.size(), 0, 0, 0);

	Instance.clear();
}

void drawable_cars::PushInstance(XMMATRIX &Model, vec4 &Color)
{
	this->Instance.push_back({Model, Color});
}