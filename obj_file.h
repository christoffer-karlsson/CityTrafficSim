#pragma once

#include "common.h"

#include <vector>

struct face
{
	uint32 Position;
	uint32 TextureCoordinate;
	uint32 Normal;
};

struct obj_file
{
	std::vector<vec3> Vertices;
	std::vector<vec3> Normals;
	std::vector<vec3> TextureUVs;
	std::vector<face> FaceIndices;
};