#include "world.h"

world::world(int32 Width, int32 Height)
{
	this->Width = Width;
	this->Height = Height;

	Tiles = new tile[Width * Height];
}

world::~world()
{
	delete [] Tiles;
}

void world::SetTile(int32 PositionX, int32 PositionY, GROUND_TYPE Type)
{
	int32 Pitch = Width * PositionY;

	Tiles[Pitch + PositionX].Type = Type;
}

int32 world::GetWidth() const
{
	return Width;
}

int32 world::GetHeight() const
{
	return Height;
}

tile &world::GetTile(int32 PositionX, int32 PositionY)
{
	int32 Pitch = Width * PositionY;

	return Tiles[Pitch + PositionX];
}
