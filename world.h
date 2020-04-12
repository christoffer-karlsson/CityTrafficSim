#pragma once

#include "common.h"
#include "terrain.h"

#include <string>
#include <vector>

#define MAX_TILE_NAMES 50

struct tile
{
	tile_type Type = tile_type::GRASS;
};

class world
{
	private:

	int32 Width;
	int32 Height;
	const real32 Size = 1.0f;

	std::string TileName[MAX_TILE_NAMES];

	tile	*Tiles;

	public:
	//TODO(Cristoffer): temp public
	terrain *Terrain;

	world(int32 Width, int32 Height);
	~world();

	void SetTile(int32 PositionX, int32 PositionY, tile_type Type);
	void SetTileHighlighted(int32 PositionX, int32 PositionY, bool SetHighlighted);

	int32 GetWidth() const;
	int32 GetHeight() const;
	std::string &GetTileName(int32 PositionX, int32 PositionY);
	tile &GetTile(int32 PositionX, int32 PositionY);
};