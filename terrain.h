#pragma once

#include "drawable.h"
#include "texture.h"
#include "light_source.h"

enum class tile_type
{
	GRASS,
	ROAD_Z,
	ROAD_X,
	CROSSROAD,
	SIDEWALK,
	WATER,
	GROUND,
	BUILDING
};

class terrain : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX MVP;
		XMMATRIX Model;
	};

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;

	uint64 WidthX;
	uint64 WidthZ;

	protected:

	texture_coordinates GetTextureCoordinateFromTileType(tile_type Type);

	public:

	terrain(uint64 WidthX, uint64 WidthZ);

	void Draw() override;

	void UpdateHighlightColorResource(vec3u Position, bool32 IsHighlighted) override;
	void UpdateTileTypeResource(vec3u Position, tile_type Type);

	uint32 GetWidthX();
	uint32 GetWidthZ();

	std::vector<vertex> &GetVertexData();
};