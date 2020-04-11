#include "world.h"

world::world(int32 Width, int32 Height)
{
	this->Width = Width;
	this->Height = Height;

	Tiles = new tile[Width * Height];

	for(uint32 Index = 0;
		Index < MAX_TILE_NAMES;
		Index++)
	{
		TileName[Index];
	}

	TileName[GRASS] = "Grass";
	TileName[ROAD_Z] = "Road in Z direction";
	TileName[ROAD_X] = "Road in X direction";
	TileName[CROSSROAD] = "Crossroad";
	TileName[SIDEWALK] = "Sidewalk";
	TileName[WATER] = "Water";
}

world::~world()
{
	delete[] Tiles;
}

void world::SetTile(int32 X, int32 Y, TILE_TYPE Type)
{
	int32 Pitch = Width * Y;

	Tiles[Pitch + X].Type = Type;
}

/*void world::SetTileHighlighted(int32 X, int32 Y, bool SetHighlighted)
{
	// TODO
}*/

int32 world::GetWidth() const
{
	return Width;
}

int32 world::GetHeight() const
{
	return Height;
}

std::string &world::GetTileName(int32 X, int32 Y)
{
	tile &Tile = GetTile(X, Y);

	return TileName[Tile.Type];
}

tile &world::GetTile(int32 X, int32 Y)
{
	int32 Pitch = Width * Y;

	return Tiles[Pitch + X];
}