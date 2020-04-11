#include "building.h"

building::building(real32 PosX, real32 PosY, real32 PosZ, real32 SizeX, real32 SizeY, real32 SizeZ)
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

	real32 XGreater = SizeX / 2.0f;
	real32 XLess = (SizeX / 2.0f) * -1.0f;
	real32 YGreater = SizeY;
	real32 YLess = 0.0f; // NOTE(Cristoffer): Make zero the ground, all size go to the height (from ground).
	real32 ZGreater = SizeZ / 2.0f;
	real32 ZLess = (SizeZ / 2.0f) * -1.0f;

	std::vector<vertex> Vertices =
	{
		  // Pos coordinates				// Texture uv coordinates						// Color/alpha values     // Vertex #
		{ XLess,	YGreater,	ZLess,		(0.0f + 0.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 1
		{ XGreater, YGreater,	ZLess,		(1.0f + 0.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 2
		{ XLess,	YLess,		ZLess,		(0.0f + 0.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 3
		{ XGreater, YLess,		ZLess,		(1.0f + 0.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 4

		{ XGreater, YGreater,	ZLess,		(0.0f + 1.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 5
		{ XGreater, YGreater,	ZGreater,	(1.0f + 1.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 6
		{ XGreater, YLess,		ZLess,		(0.0f + 1.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 7
		{ XGreater, YLess,		ZGreater,	(1.0f + 1.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 8

		{ XGreater, YGreater,	ZGreater,	(0.0f + 2.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 9
		{ XLess,	YGreater,	ZGreater,	(1.0f + 2.0f) / 3.0f, (0.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 10
		{ XGreater, YLess,		ZGreater,	(0.0f + 2.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 11
		{ XLess,	YLess,		ZGreater,	(1.0f + 2.0f) / 3.0f, (1.0f + 0.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 12

		{ XLess,	YGreater,	ZGreater,	(0.0f + 0.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 13
		{ XLess,	YGreater,	ZLess,		(1.0f + 0.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 14
		{ XLess,	YLess,		ZGreater,	(0.0f + 0.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 15
		{ XLess,	YLess,		ZLess,		(1.0f + 0.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 16

		{ XLess,	YGreater,	ZGreater,	(0.0f + 1.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 17
		{ XGreater, YGreater,	ZGreater,	(1.0f + 1.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 18
		{ XLess,	YGreater,	ZLess,		(0.0f + 1.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 19
		{ XGreater, YGreater,	ZLess,		(1.0f + 1.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 20

		{ XGreater, YLess,		ZGreater,	(0.0f + 2.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 21
		{ XLess,	YLess,		ZGreater,	(1.0f + 2.0f) / 3.0f, (0.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 22
		{ XGreater, YLess,		ZLess,		(0.0f + 2.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 23
		{ XLess,	YLess,		ZLess,		(1.0f + 2.0f) / 3.0f, (1.0f + 1.0f) / 2.0f,		1.0f, 1.0f, 1.0f, 1.0f }, // 24
	};

	std::vector<uint16> Indices =
	{
		0, 1, 2, 1, 3, 2,			// Mesh 1

		4, 5, 6, 5, 7, 6,			// Mesh 2

		8, 9, 10, 9, 11, 10,		// Mesh 3

		12, 13, 14, 13, 15, 14,		// Mesh 4

		16, 17, 18, 17, 19, 18,		// Mesh 5

		20, 21, 22, 21, 23, 22,		// Mesh 6
	};

	Shader = new shader(L"cube_vs.cso", L"cube_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	Shader->AddInputElement("AMBLIGHT", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->CommitInputElements();

	Texture = new texture(L"data/2x3_texture-2.png", 256, 256, 1, 1);

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size(), STATIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(cb));
}

void building::Draw(camera &Camera)
{
	struct cb
	{
		XMMATRIX MVP;
		XMFLOAT4 AmbientLight;

	} VS_Input;

	// NOTE(Cristoffer): Matricies need to be transposed before shader can handle them.
	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(Camera.GetViewMatrix()) * XMMATRIX(Camera.GetProjectionMatrix()));
	VS_Input.AmbientLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}