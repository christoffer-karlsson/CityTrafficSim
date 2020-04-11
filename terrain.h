#pragma once

#include "drawable.h"
#include "world.h"
#include "texture.h"

#include "mouse.h"
#include "external/SimpleMath.h"

enum TILE_TYPE;

struct terrain_vertex
{
	position	Position;
	uv			TextureCoordinate;
	real32		IsPicked;
};

class terrain : public drawable
{
	private:

	std::vector<position> WorldCoordinate;
	std::vector<terrain_vertex> Vertices;
	std::vector<uint32> Indices;

	world *World;

	protected:

	uv_quad GetTextureCoordinateFromTileType(TILE_TYPE Type);

	public:

	terrain(world *World);

	void Draw(camera &Camera) override;

	void UpdateTileHighlighResource(int32 X, int32 Y, real32 IsPicked);
	void UpdateTileTypeResource(int32 X, int32 Y, TILE_TYPE Type);

	std::vector<terrain_vertex> &GetVertexData();

	position GetWorldCoordinate(uint32 Index);
};