#include "ground.h"

ground::ground(real32 PosX, real32 PosY, GROUND_TYPE GroundType)
{
	// NOTE(Cristoffer): Since it is easier to think about ground in X,Y space,
	// it just takes those two dimensions. But Y is getting mapped to Z in data,
	// since Y is height in 3d coordinate space.
	SetModelPosition(PosX, 0.0f, PosY);

	struct cb
	{
		XMMATRIX MVP;

	} VS_Input;

	struct vertex
	{
		position Position;
		color Color;
	};

	int32 QuadCount = 0;

	std::vector<vertex> Vertices;

	for(int32 X = -50; X < 50; X++)
	{
		for(int32 Y = -50; Y < 50; Y++)
		{
			Vertices.push_back({ (real32)X - 0.5f, 0.0f, (real32)Y - 0.5f,		0.4f, 0.8f, 0.3f, 1.0f });
			Vertices.push_back({ (real32)X - 0.5f, 0.0f, (real32)Y + 0.5f,		0.4f, 0.8f, 0.3f, 1.0f });
			Vertices.push_back({ (real32)X + 0.5f, 0.0f, (real32)Y - 0.5f,		0.4f, 0.8f, 0.3f, 1.0f });
			Vertices.push_back({ (real32)X + 0.5f, 0.0f, (real32)Y + 0.5f,		0.4f, 0.8f, 0.3f, 1.0f });

			QuadCount++;
		}
	}


	std::vector<uint16> Indices;

	for(int32 Quad = 0; Quad < QuadCount; Quad++)
	{
		Indices.push_back(0 + (Quad * 4));
		Indices.push_back(1 + (Quad * 4));
		Indices.push_back(2 + (Quad * 4));
		Indices.push_back(1 + (Quad * 4));
		Indices.push_back(3 + (Quad * 4));
		Indices.push_back(2 + (Quad * 4));
	}

	/*{
		0, 1, 2, 1, 3, 2,
		4, 5, 6, 5, 7, 6,
		8, 9, 10, 9, 11, 10,
	};*/

	Shader = new shader(L"ground_vs.cso", L"ground_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->CommitInputElements();


	Texture = nullptr;

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), Vertices.size());
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint16), Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(cb));
}

void ground::Draw(camera &Camera)
{
	struct cb
	{
		XMMATRIX MVP;

	} VS_Input;

	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(Camera.GetViewMatrix()) * XMMATRIX(Camera.GetProjectionMatrix()));

	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}