#pragma once

#include "common.h"

class light_source
{
	public:

	light_source()
	{
		Position = vec3(10.0f, 10.0f, 10.0f);
	};

	static vec3 Position;
};