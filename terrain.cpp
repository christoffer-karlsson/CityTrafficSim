#include "terrain.h"

terrain::terrain(real32 PosX, real32 PosY, world *World) :
	World(World)
{
	// NOTE(Cristoffer): Since it is easier to think about ground in X,Y space,
	// it just takes those two dimensions. But Y is getting mapped to Z in data,
	// since Y is height in 3d coordinate space.
	//SetModelPosition(PosX, 0.0f, PosY);

	Texture = new texture(L"data/tile-atlas-256x256x10x10.png", 2560, 2560, 10, 10);

	struct
	{
		XMMATRIX MVP;

	} VS_Input;

	int32 QuadCount = 0;

	for(int32 X = 0; X < World->GetWidth(); X++)
	{
		for(int32 Y = 0; Y < World->GetHeight(); Y++)
		{
			real32 IsPicked = 0.0f;

			if(X == 10 && Y == 10)
			{
				IsPicked = 1.0f;
			}

			uv_quad Atlas;
			tile CurrentTile = World->GetTile(X, Y);

			if(CurrentTile.Type == GRASS)
			{
				Atlas = Texture->GetUVFromSliceCoordinates(0, 0);
			}
			else if(CurrentTile.Type == ROAD_Z)
			{
				Atlas = Texture->GetUVFromSliceCoordinates(2, 0);
			}
			else if(CurrentTile.Type == ROAD_X)
			{
				Atlas = Texture->GetUVFromSliceCoordinates(1, 0);
			}
			else if(CurrentTile.Type == CROSSROAD)
			{
				Atlas = Texture->GetUVFromSliceCoordinates(3, 0);
			}

			vertex Vertex[4];

			Vertex[0].Position.X = (real32)X - 0.5f;
			Vertex[0].Position.Y = 0.0f;
			Vertex[0].Position.Z = (real32)Y - 0.5f;
			Vertex[0].TextureCoordinate.U = Atlas.TextureCoordinate[0].U;
			Vertex[0].TextureCoordinate.V = Atlas.TextureCoordinate[0].V;
			Vertex[0].IsPicked = IsPicked;

			Vertex[1].Position.X = (real32)X - 0.5f;
			Vertex[1].Position.Y = 0.0f;
			Vertex[1].Position.Z = (real32)Y + 0.5f;
			Vertex[1].TextureCoordinate.U = Atlas.TextureCoordinate[1].U;
			Vertex[1].TextureCoordinate.V = Atlas.TextureCoordinate[1].V;
			Vertex[1].IsPicked = IsPicked;

			Vertex[2].Position.X = (real32)X + 0.5f;
			Vertex[2].Position.Y = 0.0f;
			Vertex[2].Position.Z = (real32)Y - 0.5f;
			Vertex[2].TextureCoordinate.U = Atlas.TextureCoordinate[2].U;
			Vertex[2].TextureCoordinate.V = Atlas.TextureCoordinate[2].V;
			Vertex[2].IsPicked = IsPicked;

			Vertex[3].Position.X = (real32)X + 0.5f;
			Vertex[3].Position.Y = 0.0f;
			Vertex[3].Position.Z = (real32)Y + 0.5f;
			Vertex[3].TextureCoordinate.U = Atlas.TextureCoordinate[3].U;
			Vertex[3].TextureCoordinate.V = Atlas.TextureCoordinate[3].V;
			Vertex[3].IsPicked = IsPicked;

			Vertices.push_back(Vertex[0]);
			Vertices.push_back(Vertex[1]);
			Vertices.push_back(Vertex[2]);
			Vertices.push_back(Vertex[3]);

			QuadCount++;
		}
	}

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
	Shader->AddInputElement("ISPICKED", DXGI_FORMAT_R32_FLOAT);

	Shader->CommitInputElements();

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), Vertices.size(), DYNAMIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint16), Indices.size());

	ConstantBuffer = new constant_buffer(&VS_Input, sizeof(VS_Input));
}

void terrain::Draw(camera &Camera)
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

void terrain::UpdateBuffer(int32 X, int32 Y)
{
	int32 Pitch = World->GetWidth() * 4 * Y;

	int32 Index = Pitch + (X * 4);

	if(Index + 4 > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).IsPicked = 1.0f;
	Vertices.at(Index + 1).IsPicked = 1.0f;
	Vertices.at(Index + 2).IsPicked = 1.0f;
	Vertices.at(Index + 3).IsPicked = 1.0f;

	VertexBuffer->UpdateDynamicBuffer(Vertices.data(), sizeof(vertex), Vertices.size());
}