#include "cube.h"

cube::cube(real32 PosX, real32 PosY, real32 PosZ)
{
	SetModelPosition(PosX, PosY, PosZ);

	struct cb
	{
		XMMATRIX MVP;
		XMFLOAT4 AmbientLight;

	} VS_Input;

	struct vertex
	{
		real32 X, Y, Z;
		real32 U, V;
		real32 R, G, B, A;
	};

	std::vector<vertex> Vertices =
	{
		{ -1.0f, +1.0f, -1.0f, (0.0f + 0.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 1
		{ +1.0f, +1.0f, -1.0f, (1.0f + 0.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 2
		{ -1.0f, -1.0f, -1.0f, (0.0f + 0.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 3
		{ +1.0f, -1.0f, -1.0f, (1.0f + 0.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 4

		{ +1.0f, +1.0f, -1.0f, (0.0f + 1.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 5
		{ +1.0f, +1.0f, +1.0f, (1.0f + 1.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 6
		{ +1.0f, -1.0f, -1.0f, (0.0f + 1.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 7
		{ +1.0f, -1.0f, +1.0f, (1.0f + 1.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 8

		{ +1.0f, +1.0f, +1.0f, (0.0f + 2.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 9
		{ -1.0f, +1.0f, +1.0f, (1.0f + 2.0f) / 3.0f, (0.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 10
		{ +1.0f, -1.0f, +1.0f, (0.0f + 2.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 11
		{ -1.0f, -1.0f, +1.0f, (1.0f + 2.0f) / 3.0f, (1.0f + 0.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 12

		{ -1.0f, +1.0f, +1.0f, (0.0f + 0.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 13
		{ -1.0f, +1.0f, -1.0f, (1.0f + 0.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 14
		{ -1.0f, -1.0f, +1.0f, (0.0f + 0.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 15
		{ -1.0f, -1.0f, -1.0f, (1.0f + 0.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 16

		{ -1.0f, +1.0f, +1.0f, (0.0f + 1.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 17
		{ +1.0f, +1.0f, +1.0f, (1.0f + 1.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 18
		{ -1.0f, +1.0f, -1.0f, (0.0f + 1.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 19
		{ +1.0f, +1.0f, -1.0f, (1.0f + 1.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 20

		{ +1.0f, -1.0f, +1.0f, (0.0f + 2.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 21
		{ -1.0f, -1.0f, +1.0f, (1.0f + 2.0f) / 3.0f, (0.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 22
		{ +1.0f, -1.0f, -1.0f, (0.0f + 2.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 23
		{ -1.0f, -1.0f, -1.0f, (1.0f + 2.0f) / 3.0f, (1.0f + 1.0f) / 2.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 24
	};

	std::vector<uint16> Indices =
	{
		0, 1, 2, 1, 3, 2,

		4, 5, 6, 5, 7, 6,

		8, 9, 10, 9, 11, 10,

		12, 13, 14, 13, 15, 14,

		16, 17, 18, 17, 19, 18,

		20, 21, 22, 21, 23, 22,
	};

	Shader = new shader(L"cube_vs.cso", L"cube_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	Shader->AddInputElement("AMBLIGHT", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->CommitInputElements();

	Texture = new texture(L"2x3_texture.png", 256, 256, 1, 1);

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), Vertices.size());
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint16), Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(cb));
}

void cube::Draw(camera &Camera)
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