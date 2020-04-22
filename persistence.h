#pragma once

#include "common.h"
#include "obj_file.h"
#include "world.h"

#include <fstream>
#include <string>
#include <vector>

#define OBJECT_FILES_DEFAULT_PATH "data\\objects\\"

class world;

class persistence
{
	private:

	const char *WorldSaveFile = "data\\saved_map.citysim";

	const char NEWLINE = 10;
	const char SPACE = 32;
	const char TAB = 9;

	public:

	persistence() = default;
	~persistence() = default;

	bool32 SaveWorldMap(world *World);
	bool32 LoadSavedWorldMap(world *World);

	obj_file LoadObjectFile(std::string Filename);
};