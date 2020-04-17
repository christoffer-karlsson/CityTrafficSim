#pragma once

#include "drawable.h"

class drawable_cars : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX MVP;
		XMMATRIX Model;
	};

	model *Asset;

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;

	public:

	drawable_cars(model *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color)
	{
	};

	void Draw()
	{
	};
};
