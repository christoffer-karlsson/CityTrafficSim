#include "terrain.h"

terrain::terrain(uint64 WidthX, uint64 WidthZ) :
	WidthX(WidthX),
	WidthZ(WidthZ)
{
	// NOTE(Cristoffer): Vertex positions for the collision model.
	CollisionModel.push_back(vec3(0.0f, 0.0f, 0.0f));	  // 0
	CollisionModel.push_back(vec3(0.0f, 0.0f, 200.0f));	  // 1
	CollisionModel.push_back(vec3(200.0f, 0.0f, 0.0f));	  // 2
	CollisionModel.push_back(vec3(0.0f, 0.0f, 200.0f));	  // 1
	CollisionModel.push_back(vec3(200.0f, 0.0f, 0.0f));	  // 2
	CollisionModel.push_back(vec3(200.0f, 0.0f, 200.0f)); // 3

	Texture = new texture(L"data/tile-atlas-256x256x10x10.png", 2560, 2560, 10, 10);

	int64 VertexCount = 0;

	for(uint64 X = 0; X < WidthX; X++)
	{
		for(uint64 Z = 0; Z < WidthZ; Z++)
		{
			// NOTE(Cristoffer): Forming a terrain with quads. Each quad has two triangles.
			// Storing two triangles and the two extra verticies because its needed
			// for the mouse picker, so its easier to check triangles with correct data
			// padding.

			texture_coordinates UV = Texture->GetUVFromSliceCoordinates(0, 0);

			vertex Vertex[6];

			Vertex[0].Position = vec3((real32)X - 0.5f, 0.0f, (real32)Z - 0.5f); // 0
			Vertex[1].Position = vec3((real32)X - 0.5f, 0.0f, (real32)Z + 0.5f); // 1
			Vertex[2].Position = vec3((real32)X + 0.5f, 0.0f, (real32)Z - 0.5f); // 2
			Vertex[3].Position = vec3((real32)X - 0.5f, 0.0f, (real32)Z + 0.5f); // 1
			Vertex[4].Position = vec3((real32)X + 0.5f, 0.0f, (real32)Z + 0.5f); // 3
			Vertex[5].Position = vec3((real32)X + 0.5f, 0.0f, (real32)Z - 0.5f); // 2
			
			// NOTE(Cristoffer): Normals in Y direction for now.
			Vertex[0].Normal = vec3(0.0f, 1.0f, 0.0f); // 0
			Vertex[1].Normal = vec3(0.0f, 1.0f, 0.0f); // 1
			Vertex[2].Normal = vec3(0.0f, 1.0f, 0.0f); // 2
			Vertex[3].Normal = vec3(0.0f, 1.0f, 0.0f); // 1
			Vertex[4].Normal = vec3(0.0f, 1.0f, 0.0f); // 3
			Vertex[5].Normal = vec3(0.0f, 1.0f, 0.0f); // 2

			Vertex[0].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 0
			Vertex[1].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 1
			Vertex[2].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 2
			Vertex[3].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 1
			Vertex[4].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 3
			Vertex[5].Color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // 2

			Vertex[0].TextureUVCoordinate = vec3(UV.BottomLeft, 0.0f);	// 0
			Vertex[1].TextureUVCoordinate = vec3(UV.TopLeft, 0.0f);		// 1
			Vertex[2].TextureUVCoordinate = vec3(UV.BottomRight, 0.0f); // 2
			Vertex[3].TextureUVCoordinate = vec3(UV.TopLeft, 0.0f);		// 1
			Vertex[4].TextureUVCoordinate = vec3(UV.TopRight, 0.0f);	// 3
			Vertex[5].TextureUVCoordinate = vec3(UV.BottomRight, 0.0f); // 2

			Vertex[0].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[1].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[2].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[3].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[4].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[5].HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

			Vertices.push_back(Vertex[0]);
			Vertices.push_back(Vertex[1]);
			Vertices.push_back(Vertex[2]);
			Vertices.push_back(Vertex[3]);
			Vertices.push_back(Vertex[4]);
			Vertices.push_back(Vertex[5]);

			VertexCount += 6;
		}
	}

	for(uint32 Index = 0; Index < VertexCount; Index++)
	{
		Indices.push_back(Index);
	}

	VertexShader = new vertex_shader(L"terrain_vs.cso");
	VertexShader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("NORMAL", DXGI_FORMAT_R32G32B32_FLOAT);
	VertexShader->AddInputElement("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
	VertexShader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->AddInputElement("HIGHLIGHTCOLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	VertexShader->CommitInputElements();

	PixelShader = new pixel_shader(L"terrain_ps.cso");

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size(), accessibility::Dynamic);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint32), (uint32)Indices.size());

	cbuffer_input VertexShaderInput;
	ConstantBuffer[0] = new constant_buffer(&VertexShaderInput, sizeof(VertexShaderInput));
	cbuffer_light LightBuffer;
	ConstantBuffer[1] = new constant_buffer(&LightBuffer, sizeof(LightBuffer));
}

void terrain::Draw()
{
	cbuffer_input VertexShaderInput;
	VertexShaderInput.Model = XMMatrixTranspose(Model);
	VertexShaderInput.MVP = XMMatrixTranspose(Model * 
											  XMMATRIX(camera::GetViewMatrix()) * 
											  XMMATRIX(camera::GetProjectionMatrix()));

	cbuffer_light &PixelShaderInput = light_source::GetConstantBuffer();

	VertexBuffer->UpdateDynamicBuffer(Vertices.data(), sizeof(vertex), (uint32)Vertices.size());

	Texture->Bind();
	VertexBuffer->Bind();

	VertexShader->Bind();
	ConstantBuffer[0]->Bind(0, shader_set_type::SetVertexShader);
	PixelShader->Bind();
	ConstantBuffer[1]->Bind(0, shader_set_type::SetPixelShader);

	ConstantBuffer[0]->Update(&VertexShaderInput);
	ConstantBuffer[1]->Update(&PixelShaderInput);

	direct3d::GetContext()->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}

void terrain::UpdateHighlightColorResource(vec3u Position, bool32 IsHighlighted)
{
	uint64 Index = WorldCoordinateToIndex(WidthX, 6, Position.x, Position.z);

	vec4 HighlightColor(1.0f, 1.0f, 1.0f, 1.0f);

	if(IsHighlighted)
	{
		HighlightColor = vec4(1.5f, 1.5f, 1.5f, 1.0f);
	}

	if((Index + 6) > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).HighlightColor = HighlightColor;
	Vertices.at(Index + 1).HighlightColor = HighlightColor;
	Vertices.at(Index + 2).HighlightColor = HighlightColor;
	Vertices.at(Index + 3).HighlightColor = HighlightColor;
	Vertices.at(Index + 4).HighlightColor = HighlightColor;
	Vertices.at(Index + 5).HighlightColor = HighlightColor;
}

void terrain::UpdateTileTypeResource(vec3u Position, tile_type Type)
{
	texture_coordinates UV = GetTextureCoordinateFromTileType(Type);

	uint64 Index = WorldCoordinateToIndex(WidthX, 6, Position.x, Position.z);

	if((Index + 6) > Vertices.size() || Index < 0)
	{
		return;
	}

	Vertices.at(Index + 0).TextureUVCoordinate = vec3(UV.BottomLeft, 0.0f);
	Vertices.at(Index + 1).TextureUVCoordinate = vec3(UV.TopLeft, 0.0f);
	Vertices.at(Index + 2).TextureUVCoordinate = vec3(UV.BottomRight, 0.0f);
	Vertices.at(Index + 3).TextureUVCoordinate = vec3(UV.TopLeft, 0.0f);
	Vertices.at(Index + 4).TextureUVCoordinate = vec3(UV.TopRight, 0.0f);
	Vertices.at(Index + 5).TextureUVCoordinate = vec3(UV.BottomRight, 0.0f);
}

uint32 terrain::GetWidthX()
{
	return WidthX;
}

uint32 terrain::GetWidthZ()
{
	return WidthZ;
}

texture_coordinates terrain::GetTextureCoordinateFromTileType(tile_type Type)
{
	texture_coordinates Result;

	switch(Type)
	{
		case tile_type::GRASS:		Result = Texture->GetUVFromSliceCoordinates(0, 0); break;
		case tile_type::ROAD_Z:		Result = Texture->GetUVFromSliceCoordinates(1, 0); break;
		case tile_type::ROAD_X:		Result = Texture->GetUVFromSliceCoordinates(2, 0); break;
		case tile_type::CROSSROAD:	Result = Texture->GetUVFromSliceCoordinates(3, 0); break;
		case tile_type::GROUND:		Result = Texture->GetUVFromSliceCoordinates(4, 0); break;
		case tile_type::WATER:		Result = Texture->GetUVFromSliceCoordinates(5, 0); break;
		case tile_type::BUILDING:	Result = Texture->GetUVFromSliceCoordinates(0, 9); break;

		default: Result = Texture->GetUVFromSliceCoordinates(0, 0); break;
	}

	return Result;
}

std::vector<vertex> &terrain::GetVertexData()
{
	return Vertices;
}