#pragma once

#include "common.h"
#include "world.h"

#include <fstream>
#include <string>
#include <vector>

#define OBJECT_FILES_DEFAULT_PATH "data\\objects\\"

struct obj_file
{
	std::vector<vec3> Vertices;
	std::vector<uint32> Indices;
};

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

	void SaveWorldMap(world *World);
	void LoadSavedWorldMap(world *World);
	obj_file LoadObjectFile(std::string Filename);
};