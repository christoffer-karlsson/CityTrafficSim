#pragma once

#include "drawable.h"

class cube : public drawable
{
	public:

	cube(real32 PosX, real32 PosY, real32 PosZ);

	void Draw(camera &Camera);
};