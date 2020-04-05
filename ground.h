#pragma once

#include "drawable.h"

enum GROUND_TYPE
{
	GRASS,
	ROAD,
	SIDEWALK,
	WATER,
};

class ground : public drawable
{
	public:

	ground(real32 PosX, real32 PosY, GROUND_TYPE GroundType);

	void Draw(camera &Camera);
};