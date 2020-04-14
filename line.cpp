#include "line.h"

line::line(real32 PositionX1, real32 PositionY1, real32 PositionZ1, real32 PositionX2, real32 PositionY2, real32 PositionZ2)
{
	//SetModelPosition(0.0f, 0.0f, 0.0f);

	struct
	{
		XMMATRIX MVP;

	} VS_Input;

	struct vertex
	{
		real32 X, Y, Z;
	};

	std::vector<vertex> Vertices;

	Vertices =
	{
		{PositionX1,PositionY1,PositionZ1},
		{PositionX2,PositionY2,PositionZ2},
	};

	Shader = new shader(L"line_vs.cso", L"line_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->CommitInputElements();

	Texture = nullptr;

	VertexBuffer = new vertex_buffer(Vertices.data(), (uint32)sizeof(vertex), (uint32)Vertices.size(), accessibility::Static);

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(VS_Input));
}

void line::Draw()
{
	struct cb
	{
		XMMATRIX MVP;

	} VS_Input;

	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(camera::GetViewMatrix()) * XMMATRIX(camera::GetProjectionMatrix()));

	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	direct3d::GetContext()->Draw(VertexBuffer->GetVertexCount(), 0);
}