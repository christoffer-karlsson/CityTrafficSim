#pragma once

#include "drawable.h"
#include "persistence.h"
#include "light_source.h"

struct vertex
{
	vec3 Position;
	vec4 Color;
	vec3 Normal;
};

class object : public drawable
{
	private:



	public:

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;
	std::vector<vec3> Normals;

	object(obj_file &File, vec3 Position, vec3 Scale, vec3 Rotation);

	void Draw(camera &Camera);
};