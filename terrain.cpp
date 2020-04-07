#include "terrain.h"

uv_quad terrain::GetTextureCoordinateFromTileType(TILE_TYPE Type)
{
	uv_quad Result;

	if(Type == GRASS)
	{
		Result = Texture->GetUVFromSliceCoordinates(0, 0);
	}
	else if(Type == ROAD_Z)
	{
		Result = Texture->GetUVFromSliceCoordinates(2, 0);
	}
	else if(Type == ROAD_X)
	{
		Result = Texture->GetUVFromSliceCoordinates(1, 0);
	}
	else if(Type == CROSSROAD)
	{
		Result = Texture->GetUVFromSliceCoordinates(3, 0);
	}

	return Result;
}

terrain::terrain(world *World) :
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

	uv_quad Atlas;

	tile CurrentTile;

	for(int32 X = 0; X < World->GetWidth(); X++)
	{
		for(int32 Y = 0; Y < World->GetHeight(); Y++)
		{
			CurrentTile = World->GetTile(X, Y);

			Atlas = GetTextureCoordinateFromTileType(CurrentTile.Type);

			vertex Vertex[4];

			Vertex[0].Position.X = (real32)X - 0.5f;
			Vertex[0].Position.Y = 0.0f;
			Vertex[0].Position.Z = (real32)Y - 0.5f;
			Vertex[0].TextureCoordinate.U = Atlas.TextureCoordinate[0].U;
			Vertex[0].TextureCoordinate.V = Atlas.TextureCoordinate[0].V;
			Vertex[0].IsPicked = 0.0f;

			Vertex[1].Position.X = (real32)X - 0.5f;
			Vertex[1].Position.Y = 0.0f;
			Vertex[1].Position.Z = (real32)Y + 0.5f;
			Vertex[1].TextureCoordinate.U = Atlas.TextureCoordinate[1].U;
			Vertex[1].TextureCoordinate.V = Atlas.TextureCoordinate[1].V;
			Vertex[1].IsPicked = 0.0f;

			Vertex[2].Position.X = (real32)X + 0.5f;
			Vertex[2].Position.Y = 0.0f;
			Vertex[2].Position.Z = (real32)Y - 0.5f;
			Vertex[2].TextureCoordinate.U = Atlas.TextureCoordinate[2].U;
			Vertex[2].TextureCoordinate.V = Atlas.TextureCoordinate[2].V;
			Vertex[2].IsPicked = 0.0f;

			Vertex[3].Position.X = (real32)X + 0.5f;
			Vertex[3].Position.Y = 0.0f;
			Vertex[3].Position.Z = (real32)Y + 0.5f;
			Vertex[3].TextureCoordinate.U = Atlas.TextureCoordinate[3].U;
			Vertex[3].TextureCoordinate.V = Atlas.TextureCoordinate[3].V;
			Vertex[3].IsPicked = 0.0f;

			Vertices.push_back(Vertex[0]);
			Vertices.push_back(Vertex[1]);
			Vertices.push_back(Vertex[2]);
			Vertices.push_back(Vertex[3]);

			WorldCoordinate.push_back({ (real32)X, (real32)Y });
			WorldCoordinate.push_back({ (real32)X, (real32)Y });
			WorldCoordinate.push_back({ (real32)X, (real32)Y });
			WorldCoordinate.push_back({ (real32)X, (real32)Y });

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

	// TODO(Cristoffer): Is it bad to update the dynamic buffer before drawing?
	// Should it be done earlier?
	VertexBuffer->UpdateDynamicBuffer(Vertices.data(), sizeof(vertex), Vertices.size());

	Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}

void terrain::SetTilePicked(int32 X, int32 Y, real32 IsPicked)
{
	int32 Pitch = World->GetWidth() * 4 * X;

	int32 Index = Pitch + (Y * 4);

	if(Index + 4 > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).IsPicked = IsPicked;
	Vertices.at(Index + 1).IsPicked = IsPicked;
	Vertices.at(Index + 2).IsPicked = IsPicked;
	Vertices.at(Index + 3).IsPicked = IsPicked;
}

void terrain::SetTileType(int32 X, int32 Y, TILE_TYPE Type)
{
	uv_quad Atlas = GetTextureCoordinateFromTileType(Type);

	int32 Pitch = World->GetWidth() * 4 * X;

	int32 Index = Pitch + (Y * 4);

	if(Index + 4 > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).TextureCoordinate.U = Atlas.TextureCoordinate[0].U;
	Vertices.at(Index + 0).TextureCoordinate.V = Atlas.TextureCoordinate[0].V;
	Vertices.at(Index + 1).TextureCoordinate.U = Atlas.TextureCoordinate[1].U;
	Vertices.at(Index + 1).TextureCoordinate.V = Atlas.TextureCoordinate[1].V;
	Vertices.at(Index + 2).TextureCoordinate.U = Atlas.TextureCoordinate[2].U;
	Vertices.at(Index + 2).TextureCoordinate.V = Atlas.TextureCoordinate[2].V;
	Vertices.at(Index + 3).TextureCoordinate.U = Atlas.TextureCoordinate[3].U;
	Vertices.at(Index + 3).TextureCoordinate.V = Atlas.TextureCoordinate[3].V;
}

std::vector<vertex> &terrain::GetVertexData()
{
	return Vertices;
}

position terrain::GetWorldCoordinate(uint32 Index)
{
	return WorldCoordinate.at(Index);
}
