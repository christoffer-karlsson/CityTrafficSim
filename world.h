#pragma once

#include "common.h"
#include "terrain.h"
#include "drawable_buildings.h"
#include "render_manager.h"

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

	drawable_buildings *DrawableBuildings;
	terrain *Terrain;
	tile	*Tiles;

	public:

	world(uint32 Width, uint32 Height);
	~world();

	void SetTile(vec3u Position, tile_type Type);
	void SetTileHighlighted(vec3u Position, bool32 Set);

	void UpdateBuildings();

	uint32 GetWidthX() const;
	uint32 GetWidthZ() const;
	uint32 GetTileID(vec3u Position);
	tile_type GetTileType(uint32 ID);
	std::string GetTileDescription(vec3u Position);
	tile &GetTile(vec3u Position);
	terrain *GetTerrain();
};