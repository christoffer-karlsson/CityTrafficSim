#include "ground.h"

struct uv
{
	real32 U, V;
};

struct uv_coord
{
	uv Coord[4];
};

uv_coord GetCoordinatesFromUV(real32 PositionX, real32 PositionY)
{
	uv_coord Result;

	Result.Coord[0] = { (0.0f + PositionX) / 10.0f, (0.0f + PositionY) / 10.0f };
	Result.Coord[1] = { (1.0f + PositionX) / 10.0f, (0.0f + PositionY) / 10.0f };
	Result.Coord[2] = { (0.0f + PositionX) / 10.0f, (1.0f + PositionY) / 10.0f };
	Result.Coord[3] = { (1.0f + PositionX) / 10.0f, (1.0f + PositionY) / 10.0f };

	return Result;
}

ground::ground(real32 PosX, real32 PosY, world &World)
{
	// NOTE(Cristoffer): Since it is easier to think about ground in X,Y space,
	// it just takes those two dimensions. But Y is getting mapped to Z in data,
	// since Y is height in 3d coordinate space.
	SetModelPosition(PosX, 0.0f, PosY);

	struct
	{
		XMMATRIX MVP;

	} VS_Input;

	struct vertex
	{
		position Position;
		real32 U, V;
	};

	int32 QuadCount = 0;

	std::vector<vertex> Vertices;

	for(int32 X = 0; X < World.GetWidth(); X++)
	{
		for(int32 Y = 0; Y < World.GetHeight(); Y++)
		{
			color Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			tile CurrentTile = World.GetTile(X, Y);

			uv_coord UV;

			if(CurrentTile.Type == GRASS)
			{
				UV = GetCoordinatesFromUV(0, 0);
			}
			else if(CurrentTile.Type == ROAD_Z)
			{
				UV = GetCoordinatesFromUV(2, 0);
			}
			else if(CurrentTile.Type == ROAD_X)
			{
				UV = GetCoordinatesFromUV(1, 0);
			}
			else if(CurrentTile.Type == CROSSROAD)
			{
				UV = GetCoordinatesFromUV(3, 0);
			}

			Vertices.push_back({ (real32)X - 0.5f, 0.0f, (real32)Y - 0.5f, UV.Coord[0].U, UV.Coord[0].V } );
			Vertices.push_back({ (real32)X - 0.5f, 0.0f, (real32)Y + 0.5f, UV.Coord[1].U, UV.Coord[1].V });
			Vertices.push_back({ (real32)X + 0.5f, 0.0f, (real32)Y - 0.5f, UV.Coord[2].U, UV.Coord[2].V });
			Vertices.push_back({ (real32)X + 0.5f, 0.0f, (real32)Y + 0.5f, UV.Coord[3].U, UV.Coord[3].V });

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

	Shader = new shader(L"ground_vs.cso", L"ground_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	Shader->CommitInputElements();

	Texture = new texture(L"data/tile-atlas-256x256x10x10.png", 2560, 2560, 10, 10);

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), Vertices.size());
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint16), Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(VS_Input));
}

void ground::Draw(camera &Camera)
{
	struct cb
	{
		XMMATRIX MVP;

	} VS_Input;

	VS_Input.MVP = XMMatrixTranspose(Model * XMMATRIX(Camera.GetViewMatrix()) * XMMATRIX(Camera.GetProjectionMatrix()));

	Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}