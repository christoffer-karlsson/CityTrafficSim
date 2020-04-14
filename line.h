#pragma once

#include "drawable.h"

class line : public drawable
{
	public:

	line(real32 PositionX1, real32 PositionY1, real32 PositionZ1, real32 PositionX2, real32 PositionY2, real32 PositionZ2);

	void Draw();
};