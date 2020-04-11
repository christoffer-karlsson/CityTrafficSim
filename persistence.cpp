#include "persistence.h"

void persistence::SaveWorldMap(world *World)
{
	std::ofstream File;
	File.open(WorldSaveFile);

	if(!File.is_open())
	{
		// TODO(Cristoffer): Handle file read error.
		return;
	}

	for(uint32 X = 0; X < World->GetWidth(); X++)
	{
		for(uint32 Y = 0; Y < World->GetHeight(); Y++)
		{
			File << "tile" << SPACE << X << SPACE << Y << SPACE;
			File << World->GetTile(X, Y).Type;
			File << NEWLINE;
		}
	}

	File.close();
}

void persistence::LoadSavedWorldMap(world *World, terrain *Terrain)
{
	std::string Word;

	std::ifstream File(WorldSaveFile);

	if(!File.is_open())
	{
		// TODO(Cristoffer): Handle file read error.
		return;
	}

	while(std::getline(File, Word, SPACE))
	{
		if(Word == "tile")
		{
			std::string X, Y, TileType;

			std::getline(File, X, SPACE);
			std::getline(File, Y, SPACE);
			std::getline(File, TileType, NEWLINE);
			
			World->SetTile(std::stoi(X), std::stoi(Y), (TILE_TYPE)std::stoi(TileType));
			Terrain->UpdateTileTypeResource(std::stoi(X), std::stoi(Y), (TILE_TYPE)std::stoi(TileType));
		}
		else
		{
			std::string Trash;

			std::getline(File, Trash, NEWLINE);
		}
	}

	File.close();
}