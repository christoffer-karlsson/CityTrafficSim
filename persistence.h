#pragma once

#include "common.h"
#include "world.h"
#include "terrain.h"

#include <fstream>
#include <string>

class persistence
{
	private:

	const char *WorldSaveFile = "data\\saved_map.citysim";

	const char NEWLINE = 10;
	const char SPACE = 32;

	public:

	persistence() = default;
	~persistence() = default;

	void SaveWorldMap(world *World);
	void LoadSavedWorldMap(world *World, terrain *Terrain);
};