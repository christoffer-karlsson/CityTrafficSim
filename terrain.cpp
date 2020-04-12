#include "terrain.h"

uv_quad terrain::GetTextureCoordinateFromTileType(tile_type Type)
{
	uv_quad Result;

	if(Type == tile_type::GRASS)
	{
		Result = Texture->GetUVFromSliceCoordinates(0, 0);
	}
	else if(Type == tile_type::ROAD_Z)
	{
		Result = Texture->GetUVFromSliceCoordinates(2, 0);
	}
	else if(Type == tile_type::ROAD_X)
	{
		Result = Texture->GetUVFromSliceCoordinates(1, 0);
	}
	else if(Type == tile_type::CROSSROAD)
	{
		Result = Texture->GetUVFromSliceCoordinates(3, 0);
	}
	else
	{
		Result = Texture->GetUVFromSliceCoordinates(0, 0);
	}

	return Result;
}

terrain::terrain(int64 Width, int64 Height)
{
	// NOTE(Cristoffer): Since it is easier to think about ground in X,Y space,
	// it just takes those two dimensions. But Y is getting mapped to Z in data,
	// since Y is height in 3d coordinate space.

	Texture = new texture(L"data/tile-atlas-256x256x10x10.png", 2560, 2560, 10, 10);

	struct
	{
		XMMATRIX MVP;

	} VS_Input;

	int64 QuadCount = 0;

	for(uint64 X = 0; X < Width; X++)
	{
		for(uint64 Y = 0; Y < Height; Y++)
		{
			terrain_vertex Vertex[4];

			Vertex[0].Position.x = (real32)X - 0.5f;
			Vertex[0].Position.y = 0.0f;
			Vertex[0].Position.z = (real32)Y - 0.5f;
			
			Vertex[1].Position.x = (real32)X - 0.5f;
			Vertex[1].Position.y = 0.0f;
			Vertex[1].Position.z = (real32)Y + 0.5f;
			
			Vertex[2].Position.x = (real32)X + 0.5f;
			Vertex[2].Position.y = 0.0f;
			Vertex[2].Position.z = (real32)Y - 0.5f;

			Vertex[3].Position.x = (real32)X + 0.5f;
			Vertex[3].Position.y = 0.0f;
			Vertex[3].Position.z = (real32)Y + 0.5f;

			Vertices.push_back(Vertex[0]);
			Vertices.push_back(Vertex[1]);
			Vertices.push_back(Vertex[2]);
			Vertices.push_back(Vertex[3]);

			// TODO(Cristoffer): NEEDED??
			WorldCoordinate.push_back({ vec2(X, Y) });
			WorldCoordinate.push_back({ vec2(X, Y) });
			WorldCoordinate.push_back({ vec2(X, Y) });
			WorldCoordinate.push_back({ vec2(X, Y) });

			QuadCount++;
		}
	}

	for(uint32 Index = 0; Index < QuadCount; Index++)
	{
		Indices.push_back(0 + (Index * 4));
		Indices.push_back(1 + (Index * 4));
		Indices.push_back(2 + (Index * 4));
		Indices.push_back(1 + (Index * 4));
		Indices.push_back(3 + (Index * 4));
		Indices.push_back(2 + (Index * 4));
	}

	Shader = new shader(L"ground_vs.cso", L"ground_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	Shader->AddInputElement("ISPICKED", DXGI_FORMAT_R32_FLOAT);
	Shader->CommitInputElements();

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(terrain_vertex), (uint32)Vertices.size(), DYNAMIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

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
	VertexBuffer->UpdateDynamicBuffer(Vertices.data(), sizeof(terrain_vertex), (uint32)Vertices.size());

	Texture->Bind();
	VertexBuffer->Bind();
	Shader->Bind();
	ConstantBuffer->Bind();
	ConstantBuffer->Update(&VS_Input);

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}

void terrain::UpdateTileHighlighResource(uint64 Width, int64 X, int64 Y, real32 IsHighlighted)
{
	uint64 Index = WorldCoordinateToIndex(Width, 4, X, Y);

	if((Index + 4) > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).IsHighlighted = IsHighlighted;
	Vertices.at(Index + 1).IsHighlighted = IsHighlighted;
	Vertices.at(Index + 2).IsHighlighted = IsHighlighted;
	Vertices.at(Index + 3).IsHighlighted = IsHighlighted;
}

void terrain::UpdateTileTypeResource(uint64 Width, int64 X, int64 Y, tile_type Type)
{
	uv_quad Atlas = GetTextureCoordinateFromTileType(Type);

	uint64 Index = WorldCoordinateToIndex(Width, 4, X, Y);

	if((Index + 4) > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).TextureUVCoordinate.x = Atlas.TextureCoordinate[0].U;
	Vertices.at(Index + 0).TextureUVCoordinate.y = Atlas.TextureCoordinate[0].V;
	Vertices.at(Index + 1).TextureUVCoordinate.x = Atlas.TextureCoordinate[1].U;
	Vertices.at(Index + 1).TextureUVCoordinate.y = Atlas.TextureCoordinate[1].V;
	Vertices.at(Index + 2).TextureUVCoordinate.x = Atlas.TextureCoordinate[2].U;
	Vertices.at(Index + 2).TextureUVCoordinate.y = Atlas.TextureCoordinate[2].V;
	Vertices.at(Index + 3).TextureUVCoordinate.x = Atlas.TextureCoordinate[3].U;
	Vertices.at(Index + 3).TextureUVCoordinate.y = Atlas.TextureCoordinate[3].V;
}

std::vector<terrain_vertex> &terrain::GetVertexData()
{
	return Vertices;
}

vec2 terrain::GetWorldCoordinate(uint64 Index)
{
	return WorldCoordinate.at(Index);
}
