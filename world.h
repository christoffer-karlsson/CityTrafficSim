#pragma once

#include "common.h"

#include <vector>

enum GROUND_TYPE
{
	GRASS,
	ROAD_Z,
	ROAD_X,
	CROSSROAD,
	SIDEWALK,
	WATER,
};

struct tile
{
	GROUND_TYPE Type = GRASS;
};

class world
{
	private:

	int32 Width;
	int32 Height;
	const real32 Size = 1.0f;

	tile *Tiles;

	public:

	world(int32 Width, int32 Height);
	~world();

	void SetTile(int32 PositionX, int32 PositionY, GROUND_TYPE Type);

	int32 GetWidth() const;
	int32 GetHeight() const;
	tile &GetTile(int32 PositionX, int32 PositionY);
};