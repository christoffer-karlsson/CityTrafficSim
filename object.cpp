#include "object.h"

object::object()
{
	persistence Persistence;
	obj_file File = Persistence.LoadObjectFile("taxi.obj");

	vec3 Position(0.0f, 0.0f, 0.0f);
	vec3 Scale(1.0f, 1.0f, 1.0f);
	vec3 Rotation(0.0f, 180.0f, 0.0f);

	SetInitialModel(Position, Scale, Rotation);

	struct cb
	{
		XMMATRIX MVP;
		XMFLOAT4 AmbientLight;

	} VS_Input;

	for(auto const Element : File.Vertices)
	{
		vertex Vertex;

		Vertex = { Element.x, Element.y, Element.z, 0.0f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f };

		Vertices.push_back(Vertex);
	}

	for(auto const Element : File.Indices)
	{
		Indices.push_back(Element);
	}

	Shader = new shader(L"cube_vs.cso", L"cube_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	Shader->AddInputElement("AMBLIGHT", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->CommitInputElements();

	Texture = new texture(L"data/2x3_texture-2.png", 256, 256, 1, 1);

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size(), DYNAMIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(cb));
}

void object::Draw(camera &Camera)
{
	struct cb
	{
		XMMATRIX MVP;
		XMFLOAT4 AmbientLight;

	} VS_Input;

	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(Camera.GetViewMatrix()) * XMMATRIX(Camera.GetProjectionMatrix()));
	VS_Input.AmbientLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}