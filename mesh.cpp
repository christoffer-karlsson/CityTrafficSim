#include "mesh.h"

void mesh::CreateMesh(obj_file &File)
{
	if(File.Normals.size() > 0)
	{
		HasNormals = 1;
	}

	if(File.TextureUVs.size() > 0)
	{
		HasTexture = 1;
	}

	// NOTE(Cristoffer): Store all vertex data based on the indexes.
	for(auto Index : File.FaceIndices)
	{
		vertex Vertex;

		Vertex.Position = File.Vertices.at(Index.Position);

		if(HasNormals)
		{
			Vertex.Normal = File.Normals.at(Index.Normal);
		}

		if(HasTexture)
		{
			Vertex.TextureUVCoordinate = File.TextureUVs.at(Index.TextureCoordinate);
		}

		Vertices.push_back(Vertex);

		Indices.push_back(Index.Position);
	}

	TotalSizeInBytes = sizeof(vertex) * Vertices.size() + sizeof(uint32) * Indices.size();
}

void mesh::CreateIndexedMesh(obj_file &File)
{
	for(auto E : File.Vertices)
	{
		vertex Vertex;

		Vertex.Position = vec3(E.x, E.y, E.z);
		Vertex.HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

		Vertices.push_back(Vertex);
	}

	std::vector<vec3> NormalsTemp;
	std::vector<vec3> TextureUVsTemp;

	// NOTE(Cristoffer): Store the normals and texture coordinates temporarily. 
	// They are not stored per vertex in the object files, so we have to fill them 
	// in with the indexes, so everything is grouped per vertex.
	if(File.Normals.size() > 0)
	{
		HasNormals = 1;

		for(auto E : File.Normals)
		{
			NormalsTemp.push_back(E);
		}
	}

	if(File.TextureUVs.size() > 0)
	{
		HasTexture = 1;

		for(auto E : File.TextureUVs)
		{
			TextureUVsTemp.push_back(E);
		}
	}

	// NOTE(Cristoffer): Fill the normals and texture coordinates based on mapped vertex index.
	for(auto E : File.FaceIndices)
	{
		uint32 VertexIndex = E.Position;
		uint32 NormalIndex = E.Normal;
		uint32 TextureUVIndex = E.TextureCoordinate;

		if(HasNormals)
		{
			Vertices.at(VertexIndex).Normal = NormalsTemp.at(NormalIndex);
		}

		if(HasTexture)
		{
			Vertices.at(VertexIndex).TextureUVCoordinate = TextureUVsTemp.at(TextureUVIndex);
		}
	}

	// NOTE(Cristoffer): Vertex indicies for index buffer.
	for(auto E : File.FaceIndices)
	{
		Indices.push_back(E.Position);
	}

	TotalSizeInBytes = sizeof(vertex) * Vertices.size() + sizeof(uint32) * Indices.size();
}

mesh::mesh(obj_file File, bool32 IndexedStorage)
{
	if(IndexedStorage)
	{
		CreateIndexedMesh(File);
	}
	else
	{
		CreateMesh(File);
	}
}

std::vector<vertex> &mesh::GetVertices()
{
	return Vertices;
}

std::vector<uint32> &mesh::GetIndices()
{
	return Indices;
}

uint32 mesh::GetVertexCount()
{
	return Vertices.size();
}

uint32 mesh::GetIndexCount()
{
	return Indices.size();
}

bool32 &mesh::GetHasNormals()
{
	return HasNormals;
}

bool32 &mesh::GetHaxTexture()
{
	return HasTexture;
}

uint32 &mesh::GetTotalSizeInBytes()
{
	return TotalSizeInBytes;
}
