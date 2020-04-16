#pragma once

#include "drawable.h"
#include "persistence.h"
#include "light_source.h"

class object : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX MVP;
		XMMATRIX Model;
	};

	obj_file *Asset;

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;
	std::vector<vec3> Normals;

	public:

	object(obj_file *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color);

	void Draw();
};