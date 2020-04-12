#include "world.h"

world::world(int32 Width, int32 Height) :
	Terrain(new terrain(Width, Height))
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

	TileName[tile_type::GRASS] = "Grass";
	TileName[tile_type::ROAD_Z] = "Road in Z direction";
	TileName[tile_type::ROAD_X] = "Road in X direction";
	TileName[tile_type::CROSSROAD] = "Crossroad";
	TileName[tile_type::SIDEWALK] = "Sidewalk";
	TileName[tile_type::WATER] = "Water";
}

world::~world()
{
	delete[] Tiles;
}

void world::SetTile(int32 X, int32 Y, tile_type Type)
{
	int32 Pitch = Width * Y;

	Tiles[Pitch + X].Type = Type;

	Terrain->UpdateTileTypeResource(Width, X, Y, Type);
}

void world::SetTileHighlighted(int32 X, int32 Y, bool SetHighlighted)
{
	Terrain->UpdateTileHighlighResource(Width, X, Y, SetHighlighted);
}

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