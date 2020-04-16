#include "object.h"

object::object(obj_file *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color) :
	Asset(Asset)
{
	// TODO(Cristoffer): Even if the data exists in memory it gets copier
	// per object at the moment. The because the data has to be padded in
	// such a way that the graphics driver can read it. Implement a better 
	// way down the line.

	SetInitialModel(Position, Scale, Rotation);

	// NOTE(Cristoffer): Store vertex data.
	for(auto Vert : Asset->Vertices)
	{
		vertex Vertex;

		Vertex.Position = vec3(Vert.x, Vert.y, Vert.z);
		Vertex.Normal = vec3(0.5f, 0.5f, 0.5f);
		Vertex.Color = Color;
		Vertex.HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

		Vertices.push_back(Vertex);
	}

	// NOTE(Cristoffer): Store the normals.
	for(auto Vertex : Asset->Normals)
	{
		Normals.push_back(Vertex);
	}
	
	// NOTE(Cristoffer): Fill the normal vertices based on mapped index.
	for(auto Element : Asset->FaceIndices)
	{
		uint32 VertexIndex = Element.Position;
		uint32 NormalIndex = Element.Normal;

		Vertices.at(VertexIndex).Normal = Normals.at(NormalIndex);
	}

	// NOTE(Cristoffer): Vertex indicies for index buffer.
	for(auto Indicies : Asset->FaceIndices)
	{
		Indices.push_back(Indicies.Position);
	}

	VertexShader = new vertex_shader(L"vehicle_vs.cso");
	VertexShader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	VertexShader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement("HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"vehicle_ps.cso");

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size(), accessibility::Dynamic);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

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