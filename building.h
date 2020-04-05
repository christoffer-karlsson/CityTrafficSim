#pragma once

#include "drawable.h"

class building : public drawable
{
	public:

	building(real32 PosX, real32 PosY, real32 PosZ, real32 SizeX, real32 SizeY, real32 SizeZ);

	void Draw(camera &Camera);
};