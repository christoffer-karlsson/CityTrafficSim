#pragma once

#include "drawable.h"
#include "world.h"

class ground : public drawable
{
	public:

	ground(real32 PosX, real32 PosY, world &World);

	void Draw(camera &Camera);
};