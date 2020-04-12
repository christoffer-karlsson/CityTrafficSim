#pragma once

#include "drawable.h"
#include "persistence.h"

struct vertex
{
	real32 X, Y, Z;
	real32 U, V;
	real32 R, G, B, A;
};

class object : public drawable
{
	private:



	public:

	std::vector<vertex> Vertices;
	std::vector<uint32> Indices;

	object();

	void Draw(camera &Camera);
};