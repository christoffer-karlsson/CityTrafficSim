#pragma once

#include "drawable.h"

class buildings : public drawable
{
	public:

	buildings(real32 PosX, real32 PosY, real32 PosZ, real32 SizeX, real32 SizeY, real32 SizeZ);

	void Draw();
};