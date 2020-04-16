#include "world.h"

world::world(uint32 WidthX, uint32 WidthZ) :
	Terrain(new terrain(WidthX, WidthZ))
{
	render_manager::Push(Terrain, render_layer::Terrain);

	Tiles = new tile[WidthX * WidthZ];
}

world::~world()
{
	delete[] Tiles;
}

void world::SetTile(vec3u Position, tile_type Type)
{
	uint32 Pitch = Terrain->GetWidthX() * Position.z;

	Tiles[Pitch + Position.x].Type = Type;

	Terrain->UpdateTileTypeResource(Position, Type);
}

void world::SetTileHighlighted(vec3u Position, bool32 Set)
{
	Terrain->UpdateHighlightColorResource(Position, Set);
}

uint32 world::GetWidthX() const
{
	return Terrain->GetWidthX();
}

uint32 world::GetWidthZ() const
{
	return Terrain->GetWidthZ();
}

uint32 world::GetTileID(vec3u Position)
{
	tile &Tile = GetTile(Position);

	uint32 ID = 0;

	switch(Tile.Type)
	{
		case	tile_type::GRASS:		ID = 0; break;
		case	tile_type::ROAD_Z:		ID = 1; break;
		case	tile_type::ROAD_X:		ID = 2; break;
		case	tile_type::CROSSROAD:	ID = 3; break;
		case	tile_type::SIDEWALK:	ID = 4; break;
		case	tile_type::WATER:		ID = 5; break;
	}

	return ID;
}

tile_type world::GetTileType(uint32 ID)
{
	tile_type Type = tile_type::GRASS;

	switch(ID)
	{
		case	0:		Type = tile_type::GRASS; break;
		case	1:		Type = tile_type::ROAD_Z; break;
		case	2:		Type = tile_type::ROAD_X; break;
		case	3:		Type = tile_type::CROSSROAD; break;
		case	4:		Type = tile_type::SIDEWALK; break;
		case	5:		Type = tile_type::WATER; break;
	}

	return Type;
}

std::string world::GetTileDescription(vec3u Position)
{
	tile &Tile = GetTile(Position);

	std::string Description = "NULL";

	switch(Tile.Type)
	{
		case	tile_type::GRASS:		Description = "Grass."; break;
		case	tile_type::ROAD_Z:		Description = "Road in north-south direction."; break;
		case	tile_type::ROAD_X:		Description = "Road in east-west direction."; break;
		case	tile_type::CROSSROAD:	Description = "Crossroad."; break;
		case	tile_type::SIDEWALK:	Description = "Sidewalk."; break;
		case	tile_type::WATER:		Description = "Water."; break;
	}

	return Description;
}

tile &world::GetTile(vec3u Position)
{
	uint32 Pitch = Terrain->GetWidthX() * Position.z;

	return Tiles[Pitch + Position.x];
}