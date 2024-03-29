// model.h
// Takes a object-file, and organizes the data so that a drawable
// can reuse it easily.

#pragma once

#include "obj_file.h"

// NOTE(Cristoffer): Make sure to line up vertex input elements correctly.
struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec3 TextureUVCoordinate;
	vec4 Color;
	vec4 HighlightColor;

	vertex()
	{
		// NOTE(Cristoffer): Defaults so that drawables that don't use
		// them don't need to define them.
		Color = vec4(1.0f, 0.2f, 0.8f, 1.0f);
		Normal = vec3(0.0f, 0.0f, 0.0f);
		HighlightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		TextureUVCoordinate = vec3(0.0f, 0.0f, 0.0f);
	}
};

class mesh
{
	private:

	bool32 HasNormals = 0;
	bool32 HasTexture = 0;

	uint32 TotalSizeInBytes;

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;

	// NOTE(Cristoffer): Creates a mesh for rendering _without_ indices. This is useful
	// if the object has sharp corners (for example a cube), where we need three different
	// normals for the same vertex depending on the face.
	void CreateMesh(obj_file &File);

	// NOTE(Cristoffer): Creates a mesh for rendering _with_ indices. 
	// This will take one normal for connecting vertices, which will then make a smoother
	// look. Use for more complex models, like spheres.
	void CreateIndexedMesh(obj_file &File);

	public:

	mesh(obj_file File, bool32 IndexedStorage);

	std::vector<vertex> &GetVertices();
	std::vector<uint32> &GetIndices();
	uint32 GetVertexCount();
	uint32 GetIndexCount();
	bool32 &GetHasNormals();
	bool32 &GetHaxTexture();
	uint32 &GetTotalSizeInBytes();
};