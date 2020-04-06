#pragma once

#include "drawable.h"
#include "world.h"
#include "texture.h"

struct vertex
{
	position	Position;
	uv			TextureCoordinate;
	real32		IsPicked;
};

class terrain : public drawable
{
	private:

	std::vector<vertex> Vertices;
	std::vector<uint16> Indices;

	world *World;

	public:

	terrain(real32 PosX, real32 PosY, world *World);

	void Draw(camera &Camera) override;

	void UpdateBuffer(int32 X, int32 Y);
};